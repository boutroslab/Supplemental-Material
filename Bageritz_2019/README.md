
# Software for Gene expression atlas of a developing tissue by single cell expression correlation analysis

The directory contains all the software necessary to run the analysis contained in the publication __Bageritz, J., Willnow, P., Valentini, E., Leible, S., Boutros, M., & Teleman, A. A. (2018). Gene expression atlas of a developing tissue by single cell expression correlation analysis. BioRxiv, 477125. https://doi.org/10.1101/477125__.

In particular, the directory __SRG_method__ contains an Rmarkdown tutorial that explains step by step how to obtain the Spatially Restricted Genes (SRGs).

The directory __Software_package__ instead, contains 4 scripts that will allow you to create a Gene expression maps from single-cell sequencing data using gene expression correlations.

## Getting Started

The SRG_method_tutorial.Rmd can be run with the example dataset provided in the directory (raw.data.txt) or with your own dataset providing that is in a matrix format with one gene per row and one cell per column.

Instructions how to run the scripts contained in the software package are in the internal README file.

### Prerequisites

You should have _R_ and _C_ installed in your system.
For _R_ you will need the package __tidyverse__
Details about the Software package prerequisite are included in the internal README file.
