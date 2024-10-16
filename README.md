Experiments on growth series of braid groups
============================================

This repository gives a frameword to investigate growth series of braids groups with at most 4 strands.
The set of generators can be the Artin's one or the the Birman--Ko--Lee's one, also known, as dual generators.

The desciption of the algorithm and its math is given in [1]


Results
=======

Below is the table of the first terms of the sherical and geodesical series of $B_4$ with respect to Artin's generators. A CSV files with more stats is available here https://github.com/jfromentin/gbraids/blob/master/results/artin_4_25.csv

l | numbers of braids | number of geodesic words
--|-------------------|--------------------------
0 |1                  |1
1 |6                  |6
2 |26                 |30
3 |98                 |142
4 |338                |646
5 |1110               |2870
6 |3542               |12558
7 |11098              |54026
8 |34362              |229338
9 |105546             |963570
10|322400             |4016674
11|980904             |16641454
12|2975728            |68614150
13|9007466            |281799158
14|27218486           |1153638466
15|82133734           |4710108514
16|247557852          |19186676438
17|745421660          |78004083510
18|2242595598         |316591341866
19|6741618346         |1283041428650
20|20252254058        |5193053664554
21|60800088680        |20994893965398
22|182422321452       |84795261908498
23|547032036564       |342173680884002
24|1639548505920      |1379691672165334
25|4911638066620      |5559241797216166

Below is the table of the first terms of the sherical and geodesical series of $B_4$ with respect to Birman--Ko--Lee's generators. A CSV files with more stats is available here https://github.com/jfromentin/gbraids/blob/master/results/dual_4_14.csv

l | numbers of braids | number of geodesic words
--|-------------------|--------------------------
0 |1                  |1
1 |12                 |12
2 |84                 |132
3 |478                |1340
4 |2500               |12788
5 |12612              |117452
6 |62570              |1053604
7 |307756             |9311420
8 |1506212            |81488628
9 |7348366            |708368540
10|35773324           |6128211364
11|173885572          |52826999612
12|844277874          |454136092148
13|4095929948         |3895624824092
14|19858981932        |33359143410468
15|96242356958        |285259736104444

Note that a typo for l = 7 appears in [1], the correct value is 307 756 as in the previous table.
We thank M. Bousquet-Mélou to point out this typo. 

Reference
=========

[1] Jean Fromentin. 2022. Experiments on growth series of braid groups. Journal of Algebra 607 (2022), 232-259.
DOI:https://doi.org/10.1016/j.jalgebra.2021.04.040
