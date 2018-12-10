# CKMeansTreeClustering
A new fast method for building multiple consensus trees using *k*-means

# About
	=> =============================================================================================================
	=> Program   : KMeansTreeClustering - 2018 (supe
	=> Authors   : Nadia Tahiri and Vladimir Makarenkov (Universite du Quebec a Montreal)
	=> This program computes a clustering of phylogenetic trees based on the *k*-means partitioning algorithm.
	=> The set of trees in the Newick format should be provided as input.
	=> The optimal partitioning in K classes is returned as output. The number of classes can be determined by the
	=> Calinski-Harabasz and W criterion for cluster validity indices adapted for tree clustering.
	=> The non-squared of Robinson and Foulds topological distance can be used.
	=> The recommended option: Calinski-Harabasz + non-squared Robinson and Foulds distance.
	 =============================================================================================================

# Installation
	$ git clone https://github.com/TahiriNadia/CKMeansTreeClustering.git
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
