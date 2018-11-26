all: createTree_ConsensusTrees_simulations.cpp
	g++ createTree_ConsensusTrees_simulations.cpp -openmp -g -o cSuperTree
	chmod -R 777 * .
	@echo "Please execute next command line:"
	@echo '===> For simulation: ./cSuperTree -simulation number_species percent_nose number_of_simulation int_parameter'
	@echo '===> For trees: ./cSuperTree -tree nameFile_trees int_parameter'
	@echo '===> For matrice: ./cSuperTree -matrice nameFile_matrice int_parameter'
	@echo ' '
	@echo '===> ========================================================================================================'
	@echo '===> Program : K-Means super-trees - 2015'
	@echo '===> Authors   : Nadia Tahiri and Vladimir Makarenkov (Universite du Quebec a Montreal)'
	@echo '===> This program computes a clustering for phylogenetic trees based on the K-Means partitioning.'
	@echo '===> ========================================================================================================'
	@echo ' '
	
install: createTree_ConsensusTrees_simulations.cpp
	g++ createTree_ConsensusTrees_simulations.cpp -openmp -g -o cSuperTree
	chmod -R 777 * .
	@echo "Please execute next command line:"
	@echo '===> For simulation: ./cSuperTree -simulation number_species percent_nose number_of_simulation int_parameter'
	@echo '===> For trees: ./cSuperTree -tree nameFile_trees int_parameter'
	@echo '===> For matrice: ./cSuperTree -matrice nameFile_matrice int_parameter'
	@echo ' '
	@echo '===> ========================================================================================================'
	@echo '===> Program : K-Means super-trees - 2015'
	@echo '===> Authors   : Nadia Tahiri and Vladimir Makarenkov (Universite du Quebec a Montreal)'
	@echo '===> This program computes a clustering for phylogenetic trees based on the K-Means partitioning.'
	@echo '===> ========================================================================================================'
	@echo ' '
	
clean: 
	$(RM) cSuperTree