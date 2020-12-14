This folder contains a CRISPR/Cas9 Library with the following features:

1. Files contained in this folder and their content:
	*.fasta
		-a fasta file containing the ready to order olives with the respective target site and the vector parts
		-the fasta file is made for a 12 K library of CustomArrays, which comprises a total of 12472 sgRNA designs
		-each fasta file includes 12080 designs for 604 genes, 200 designs for 10 positive (killing controls), 192 designs for negative control (random designs) 	


2. The sub library was chosen from the larger library by the following algorithm
	1. Sort the entire list hierachical by
			gene_id
				annotation score
					specificity score
						efficiency score
	2. Provide no cut-offs
						
	3. Go through the list and take always the first 20 designs for each gene if the following criteria are matched
		1. the overall number is smaller than 12080
		2. sequence does not contain one of the following sequences:
			GAAGAC, GAATTC, CTTAAG, CAATTG, GTTAAC, CTCGAG, GAGCTC 
			
	4. Exchange the most 5' base of every design by a G
	
	5. check  if the gene got 20 designs
		if not discard it completely
	
	