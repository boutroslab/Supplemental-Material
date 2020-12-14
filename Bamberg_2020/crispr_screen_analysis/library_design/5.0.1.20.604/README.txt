This folder contains a CRISPR/Cas9 Library with the following features:

1. Files contained in this folder and their content:
	*.coverage.tab
		-a tab-stopp separated table with two columns: first ensembl ids in the library
		, second how many designs are in the library targeting this gene
	*.fasta
		-a fasta file containing the ready to order olgios with the respective target site and the vector parts
	*.gff
		-a "General Feature Format" file containing all designs that made it into the library
		for more infomation see http://www.sanger.ac.uk/resources/software/gff/spec.html
		for view in the ensembl genome browser see http://www.ensembl.org/info/website/upload/index.html
	*.large.gff
		-a "General Feature Format" file containing all designs that could have made it into the library
		for more infomation see http://www.sanger.ac.uk/resources/software/gff/spec.html
		for view in the ensembl genome browser see http://www.ensembl.org/info/website/upload/index.html
	*.large.tab
		-a tab-delimited E-CRISP-Libedit result table with the following columns
			Name	Length	Start	End	Strand	Nucleotide sequence	Gene Name	Transcripts	Transcript:: Exon	
			Number of Cpg Islands hit	Sequence around the cutside	%A %C %T %G	S-Score	A-Score	E-Score	
			percent of total transcripts hit	Target	Match-start	Match-end	Matchstring	Editdistance	
			Number of Hits	Direction
		-this table contains one row for every target of every design, thus if one design has several lines,
		each additional line is one off-target hit
		-the table is tab-delimited
	*.tab
		-a tab-delimited E-CRISP-Libedit result table with the following columns
			Name	Length	Start	End	Strand	Nucleotide sequence	Gene Name	Transcripts	Transcript:: Exon	
			Number of Cpg Islands hit	Sequence around the cutside	%A %C %T %G	S-Score	A-Score	E-Score	
			percent of total transcripts hit	Target	Match-start	Match-end	Matchstring	Editdistance	
			Number of Hits	Direction
		-this table contains on row for every design that made it into the library
		-the table is sorted by gene, annotation score, specificity score, efficiency score
		-the table is tab-delimited
	*.missing.tab
		a table like the coverage table for every gene from the initial library that has not made into the subset library

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
	
	