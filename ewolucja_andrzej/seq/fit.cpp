#include <omp.h>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

constexpr long n = 2;
constexpr double LOWER_BOUND = -40.0;
constexpr double UPPER_BOUND = 40.0;
constexpr double prob = 0.3;

double randomDouble(const double& min, const double& max) {
	static thread_local std::mt19937 generator(omp_get_thread_num());
	std::uniform_real_distribution<double> dist(min, max);
	return dist(generator);
}

int main()
{
	std::vector<double> points(n);
	double time_start, run_time;

	int max_threads = omp_get_max_threads();
	printf("MAX THREADS: %d\n", max_threads);
	omp_set_num_threads(max_threads);

	time_start = omp_get_wtime();

	for (unsigned int i = 0; i < points.size(); ++i) {
		points[i] = randomDouble(LOWER_BOUND, UPPER_BOUND);
	}

	double sum = 0.0, product = 1.0;

	for (unsigned int j = 0; j < points.size(); ++j) {
		product *= std::cos(points[j]/(j + 1));
	}
	for (unsigned int i = 0; i < points.size(); ++i) {
		sum += points[i] * points[i];
	}
	for (unsigned int i = 0; i < points.size(); ++i) {
		if (randomDouble(0.0, 1.0) <= prob) {
			double change = randomDouble(-points[i]/5, points[i]/5);
			points[i] += change;
		}
	}

	run_time = omp_get_wtime() - time_start;
	
	double fit = (1.0/40.0) * sum + 1 - product;

	std::cout <<"przystosowanie: " << fit << std::endl;
	std::cout <<"czas: " << run_time << std::endl;
	
}