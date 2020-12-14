Workflow

1. Advanced Search in UniProt for keyword (XXX) AND organism: homo sapiens.

2. Match UniProt ID in DAVID to Ensembl Gene ID
-> 85% of UniProt ID can be matched, ~ 10% ambiguous, ~ 5% cannot be matched
-> list of matched and ambiguous genes generated (LIST1)
-> non-matched list where entered in UniProt for matching and matches were added to LIST1

3. Removal of duplicates
-> search LIST1 for duplicates in Ensembl Gene ID and remove
-> search LIST1 for mulitple Ensembl Gene IDs matching to same UniProt ID, enter those ENSEMBL Gene in ENSEMBL, then remove all non primary assemble genes
-> final list LIST2

