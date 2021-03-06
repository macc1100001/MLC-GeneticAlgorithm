#include "genalg.h"

static void get_individual(uint dest[], uint destSize,
                           uint *src, uint idx){
    for(uint i = 0; i < destSize; i++){
        dest[i] = src[idx*destSize + i];
    }
}

static void append_individual(uint *dest, uint ind,
                              uint *src, uint srcSize){
    for(uint j = 0; j < srcSize; j++)
        dest[ind*srcSize + j] = src[j];
}

static int find_zero_idx(uint arrSize, uint arr[]){
    for(uint i = 0; i < arrSize; i++){
        if(arr[i] == 0)
            return i;
    }
    return -1;
}

static int cmpfnc(const void *a, const void *b){
    return (*(uint*)a - *(uint*)b);
}

static void mutation_prob(bool mutvect[], uint popSize,
                    double pMut, const gsl_rng *r){
    for(uint i = 0; i < popSize; i++)
        mutvect[i] = (bool)gsl_ran_bernoulli(r, pMut);
}

static void crossing_prob(bool crossvect[], uint popSize,
                      double pCross, const gsl_rng *r){
    for(uint i = 0; i < popSize; i++)
        crossvect[i] = (bool)gsl_ran_bernoulli(r, pCross);
}

static void crossover(uint crossed[], uint ind1[],
                      uint ind2[], uint queens){

    /*  Current implementation only works for 8-Queen.
        Redefine this crossover function to make it work for N-Queen
     */
    uint ind2cpy[queens];
    memcpy(ind2cpy, ind2, queens*sizeof(uint));        
    uint start = 2, end = 6;
    
    for(uint i = 0; i < queens; i++){
        for(uint j = start; j < end; j++){
            if(ind1[j] == ind2cpy[i])
                ind2cpy[i] = 0;
        }
    }
          
    uint j = 0;
    for(uint i = 0; i < queens; i++){
        if(i >= start && i < end)
            crossed[i] = ind1[i];
        else{
            for(; j < queens; j++){
                if(ind2cpy[j] != 0){
                    crossed[i] = ind2cpy[j++];
                    break;
                }
            }
        }
    }
}

static uint get_fitness(uint ind[], uint queens, int sel){
    uint i; 
    int fitness = queens*queens;
    if(sel == 2){
        int sum = 0;
        for(i = 0; i < queens - 1; i++){
            sum += abs(ind[i] - ind[i + 1]);
        }
        fitness = 2 * (queens - 1) - sum;
    }
    else if(sel == 1){
        uint diag1 = 0, diag2 = 0;
        uint s1[queens], s2[queens];
        
        for(i = 0; i < queens; i++){
            s1[i] = ind[i] - i;
            s2[i] = 1 + queens - ind[i] - i;
        }
        
        qsort(s1, queens, sizeof(uint), cmpfnc);
        qsort(s2, queens, sizeof(uint), cmpfnc);
        
        
        for(i = 1; i < queens; i++){
            if(s1[i] == s1[i - 1])
                diag1++;
            if(s2[i] == s2[i - 1])
                diag2++;
        }
        
        
        fitness = diag1 + diag2;
    }

    return fitness;
}


static void cross(uint crossed[], uint **selected, uint popSize,
                  uint queens, double pCross, const gsl_rng *r){
    
    bool toCross[popSize];
    crossing_prob(toCross, popSize, pCross, r);
        
    gsl_ran_shuffle(r, selected, popSize, sizeof(uint*));  
    
    uint temp1[queens], temp2[queens];
    
    for(uint i = 0; i < popSize; i++){
        uint next = (i == (popSize - 1)) ? 0 : i + 1;
        memcpy(temp1, &selected[next][0], queens * sizeof(uint));
        memcpy(temp2, &selected[i][0], queens * sizeof(uint));
        if(toCross[i]){
            uint tmpCross[queens];
            crossover(tmpCross, temp1, temp2, queens);
            append_individual(crossed, i, tmpCross, queens);
        }
        else{
            append_individual(crossed, next, temp1, queens);
            append_individual(crossed, i, temp2, queens);
        }
            
    }
}


static void mutate(uint mutated[], uint currGen[], uint popSize,
                   uint queens, double pMut, const gsl_rng *r){
    
    bool toMutate[popSize];
    uint toChange[2], idxs[queens], tmpMutated[queens], tmp[queens];
    mutation_prob(toMutate, popSize, pMut, r);
    for(uint i = 0; i < queens; i++)
        idxs[i] = i;
    for(uint i = 0; i < popSize; i++){
        if(toMutate[i]){
            uint c1, c2;
            gsl_ran_choose(r, toChange, 2, idxs, queens, sizeof(uint));
            get_individual(tmp, queens, currGen, i);
            memcpy(tmpMutated, tmp, queens * sizeof(uint));
            c1 = tmpMutated[toChange[0]];
            c2 = tmpMutated[toChange[1]];
            tmpMutated[toChange[0]] = c2;
            tmpMutated[toChange[1]] = c1;
            append_individual(mutated, i, tmpMutated, queens);
        }
        else{
            get_individual(tmp, queens, currGen, i);
            append_individual(mutated, i, tmp, queens);
        }
    }
}

static void selection(int sel, uint **listSelected, uint popSize,
                      uint queens, uint currGen[], uint fitness[],
                      const gsl_rng *r){

    if(sel){    
        printf("Implement tournament selection...\n");
        abort();
    }
    else{
        //printf("Roulette selection\n"); /* for debugging */
        uint sum = 0;
        for(uint i = 0; i < popSize; i++)
            sum += queens - fitness[i];
            
        uint random, acum;
            
        for(uint i = 0; i < popSize; i++){
            random = (uint)gsl_rng_uniform_int(r, sum + 1);
            acum = 0;
            for(uint j = 0; j < popSize; j++){
                acum += queens - fitness[j];
                if(acum >= random){
                    uint tmpInd[queens];
                    get_individual(tmpInd, queens, currGen, j);
                    listSelected[i] = (uint*)calloc(queens, sizeof(uint));
                    if(listSelected[i] != NULL){
                        memcpy(&listSelected[i][0], tmpInd,
                               queens * sizeof(uint));
                    }
                    break;
                }
            }
        }
    }
        
}

ga_solution* ga_solver(uint queens, uint popSize,
               uint maxGens, int selflag, bool verboseflag,
               double pMut, double pCross){

    const gsl_rng_type * T;
    gsl_rng * r;

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    
    ga_solution *tmpsol;
    tmpsol = (ga_solution*)malloc(sizeof(ga_solution));
    if(tmpsol == NULL){
        //fprintf(stderr, "Couldn't allocate memory\n");
        gsl_rng_free(r);
        return NULL;
    }
    
    tmpsol->queens = queens;
    tmpsol->generation = 0;

    uint currGen[popSize * queens];
    bool finished = false;
    
    uint nums[queens];
    for(uint i = 0; i < queens; i++)
        nums[i] = i + 1;
            
    for(uint i = 0; i < popSize; i++){
        gsl_ran_shuffle(r, nums, queens, sizeof(uint));
        append_individual(currGen, i, nums, queens);
    }
        
    
    for(uint generation = 1; (generation <= maxGens) && !finished; generation++){
        uint fitness[popSize];
        for(uint i = 0; i < popSize; i++){
            uint ind[queens];
            get_individual(ind, queens, currGen, i);
            fitness[i] = get_fitness(ind, queens, 1);
        }
        
        if(verboseflag){
            printf("Generation: %d\n", generation);
            printf("fitness = [ ");
            for(uint i = 0; i < popSize; i++)
                printf((i == (popSize - 1)) ? "%d " : "%d, ", fitness[i]);
            printf("]\n\n");
        }
        
        int idx = find_zero_idx(queens, fitness);
        if(idx != -1){
            uint tmp[queens];
            get_individual(tmp, queens, currGen, idx);
            tmpsol->solution = (uint*)calloc(queens, sizeof(uint));
            if(tmpsol->solution != NULL)
                memcpy(tmpsol->solution, tmp, queens * sizeof(uint));
            tmpsol->generation = generation;
            finished = true;
            continue;
        }
        
        uint **selected = (uint**)calloc(popSize, sizeof(uint*));
        if(selected == NULL){
            fprintf(stderr, "Could not allocate memory for selected array.\n");
            ga_free_sol(tmpsol);
            return NULL;
        }
                
        selection(selflag, selected, popSize, queens, 
                        currGen, fitness, r);
                                
        uint crossed[popSize * queens];
        cross(crossed, selected, popSize, queens, pCross, r);
                
        uint mutated[popSize * queens];
        mutate(mutated, crossed, popSize, queens, pMut, r);
        
        memcpy(currGen, mutated, popSize * queens * sizeof(uint));   
        	    
        for(uint i = 0; i < popSize; i++)
            free(selected[i]);
        free(selected);
    }
    //memcpy(sol, &tmpsol, sizeof(ga_solution));
    //free(tmpsol.solution);
    gsl_rng_free(r);
    return tmpsol;
}

void ga_free_sol(ga_solution *sol){
    free(sol->solution);
    free(sol);
}

