#include "candidate.h"
#include "evolution.h"
#include <omp.h>

int main()
{
	std::vector<double> cnds(n);
	double time_start, run_time;

	int max_threads = omp_get_max_threads();
	printf("MAX THREADS: %d\n", max_threads);
	omp_set_num_threads(max_threads);
	omp_set_nested(1);

	time_start = omp_get_wtime();

	// double sum = 0.0, product = 1.0;
	
	// #pragma omp parallel
	// {	
	// 	thread_local std::mt19937 generator(omp_get_wtime());
	// 	std::uniform_real_distribution<double> dist(LOWER_BOUND, UPPER_BOUND);
	// 	#pragma omp for schedule(static, 1)
	// 	for (unsigned int i = 0; i < cnds.size(); ++i) {
	// 		cnds[i] = randomDouble(LOWER_BOUND, UPPER_BOUND);
	// 	}
	// 	#pragma omp for reduction(*:product) reduction(+:sum) schedule(static, 1) nowait
	// 	for (unsigned int j = 0; j < cnds.size(); ++j) {
	// 		product *= std::cos(cnds[j]/(j + 1));
	// 		sum += cnds[j] * cnds[j];
	// 	}
	// 	#pragma omp for schedule(static, 1)
	// 	for (unsigned int i = 0; i < cnds.size(); ++i) {
	// 		if (randomDouble(0.0, 1.0) <= PROB_MUT_POINT) {
	// 			cnds[i] = randomDouble(-cnds[i]/5, cnds[i]/5);
	// 		}
	// 	}
	// 	// #pragma omp for reduction(+:sum) nowait
	// 	// for (unsigned int i = 0; i < cnds.size(); ++i) {
	// 	// 	sum += cnds[i] * cnds[i];
	// 	// }
	// }

	// double fit = (1.0/40.0) * sum + 1 - product;

	// run_time = omp_get_wtime() - time_start;
	
	// //std::cout <<"przystosowanie: " << fit << std::endl;
	// std::cout <<"czas: " << run_time << std::endl;

	int t = 1000;
	time_start = omp_get_wtime();
	Evolution evo(3, 10, 2);
	for (int i = 0; i < t; ++i) {
		evo.evolve();
	}
	evo.show_all();
	run_time = omp_get_wtime() - time_start;
	//evo.show_all();
	std::cout <<"czas: " << run_time << std::endl;
}