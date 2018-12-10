# CKMeansSuperTreeClustering
A new fast method for building multiple consensus trees using *k*-means

# About
	=> =============================================================================================================
	=> Program   : KMeansSuperTreeClustering - 2018
	=> Authors   : Nadia Tahiri and Vladimir Makarenkov (Université du Québec a Montréal)
	=> This program clusters phylogenetic trees based using the k-means partitioning algorithm.
	=> These trees may have the same or different, but mutually overlapping, sets of leaves.
	=> Phylogenetic trees must be given in the Newick format (program input).
	=> A partitioning of the input trees in K clusters of trees is returned as output. 
	=> The optimal number of classes can be determined either by the Calinski-Harabasz or by the Ball-Hall cluster validity
	=> index adapted for tree clustering.
	=> The Robinson and Foulds topological distance is used in the objective function of K-means.
	=> The list of the program parameters is specified below.
	 =============================================================================================================

# Installation
	$ git clone https://github.com/TahiriNadia/KMeansSuperTreeClustering.git
	$ make
	or
	$ make install

	clean project
	$ make clean

# Help
	$ make help

# Examples
	Please execute the following command line:
	=> For trees: ./KMTC -tree input_file criterion

	Input_file - the input file for the program
	criterion - the criterion for the k-medoids algorithm (1, 2, 3 or 4, see below)

	List of criteria for the k-medoids algorithm:
	=> criterion 1 - CH (Calinski-Harabasz) with RF (Robinson and Foulds distance)
	=> criterion 2 - W criterion with RF

  => Kmin: is a number of minimum value cluster. This criterion can be change.
      - For CH, Kmin­>=2
      - For W, Kmin>=1

  => Kmax: is a number of maximum value cluster. This criterion can be change.
      - The maximum is less or egal to N-1 with N is the number of trees (for CH or W).

  => alpha: is a number of factor of RF value.

	Command line execution:
	./KMTC -tree data/all_trees_woese.txt -p 1 -alpha 1 -kmin 2 -kmax 3

# Input
	=> See the folder "data"
	Phylogenetic trees in the Netwick format (see the example in: data/all_trees_woese.txt)

# Output
	=> See the folder "output"
	The output is in the following files:
	1) stat.csv - for clustering statistics;
	2) output.txt - for cluster content.
