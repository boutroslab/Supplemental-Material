reannotate-crispr is a perl based script for the re-annotation or the mapping of existing sgRNA libraries. it relies on the same architecture a E-CRISP (e-crisp.org) and cld (github.com/boutroslab/cld).

It depends on the following perl packages available from the CRAN archive:

 Bio::DB::Fasta
 Bio::SeqIO
 Bio::Tools::GFF
 Scalar::Util
 Bio::SeqFeature::Generic
 Bio::Location::Split
 JSON::XS 
 File::Slurp
 List::MoreUtils 
 List::Util 
 Archive::Zip
 Parallel::ForkManager
 Cwd
 Getopt::Long
 File::Grep
 Text::Wrap
 Unix::Processors
 
 , and the package Set::IntervalTree, which can be found in the depends folder of this directory.

Databases can be downloaded from http://www.dkfz.de/signaling/crispr-downloads/


    Usage: perl reannotate-crispr.pl [--options=value] ...
    
         Options:
         
             --output-dir=<path/to/dir>          - A working directory as unix path to directory. (default: .)
             
             --sequence-files=<path/to/dir>      - A fasta formatted file of sgRNA spacer sequences (not-including PAM, mandatory).
             
             --databasepath=<path/to/dir>        - Select folder where genome data is deposit  (default: .)
             
             --organism=<string>                 - Please type the name of the reference organism as given in the database (default: drosophila_melanogaster)
             
             --non-seed-length=<int>             - Specify the non-seed length in bp (the number of 5' basepairs to be ignore by the aligner, default: 1)
             
             --mismatches-allowed=<int>          - Specify the number of mismatches allowed in a "valid" alignment (default: 0)
             
             --version                           - Show version.
             
             --help                              - Show this message.
