The following Ideas are behind the given parameter file:

Library Preparation from gene lists
1.	Gene lists must be given as ENSEMBL identifiers existing in the newest ENSEMBL release. If this is unclear or can’t be checked all IDs, which don’t exist in E-CRISPs database will be ignored.
2.	Gene lists will be uploaded to E-CRISP and run with highly relaxed standard parameters.
	a.	{20}NGG
	b.	Higher scoring for sequences preceded by GG (Kim et al.) and enriched fort higher GC content at their 3’ end (Lander et al.) and overall good GC content
	c.	Targeting anywhere in the gene
	d.	Being annotated with all kinds of genome annotations (exons, transcripts …)
	e.	Relaxed GC content (10 -90 %)
	f.	Off-target checked as {3}N117NGG allowing 2-3 Mismatches
3. Library should only contain designs likely to cause LoF function alleles in protein coding genes

