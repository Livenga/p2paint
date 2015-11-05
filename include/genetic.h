#ifndef GENETIC_H
#define GENETIC_H

/* 終了世代 */
#define NUMBER_OF_GENERATION (10000)

/* 個体, 子個体数 */
#define POPULATION_SIZE (20)
#define CHILDREN_SIZE   (10)

/* 突然変異, 交叉率 */
#define MUTATION_RATE  (1.0)
#define CROSSOVER_RAGE (0.7)

/* パッチ半径 */
#define INIT_PATCH_SIZE (80) /* 初期個体生成  */
#define PATCH_SIZE      (40) /* GAパラメータ  */

/* src/genetic/gn_calc.c */
extern int
minof_fitness(int population,
              double *fitness);
#endif
