#reannotate-crispr 
is a perl based script for the re-annotation or the mapping of existing sgRNA libraries. it relies on the same architecture a E-CRISP (http://www.e-crisp.org) and cld (http://github.com/boutroslab/cld).

It depends on the following perl packages available from the CPAN archive:

 Bio::DB::Fasta<br>Bio::SeqIO<br>Bio::Tools::GFF<br>Scalar::Util<br>Bio::SeqFeature::Generic<br>Bio::Location::Split<br>JSON::XS<br>File::Slurp<br>List::MoreUtils<br>List::Util<br>Archive::Zip<br>Parallel::ForkManager<br>Cwd<br>Getopt::Long<br>File::Grep<br>Text::Wrap<br>Unix::Processors<br>
 
 , and a **modified** package Set::IntervalTree, which can be found in the depends folder of this directory.

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
