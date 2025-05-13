#!/bin/sh


#SBATCH --job-name=wgs_fastqc  	# Job name
#SBATCH --cpus-per-task=40     	# Run on a single CPU
#SBATCH --mem=256gb             	# Job memory request
#SBATCH --time=1:30:00       	# Time limit hrs:min:sec
#SBATCH --output=fastqc_slurm.log  # Standard output and error log
#SBATCH --partition=short

cd ~/homeworks/hw_12/genomics/trimmed/fastqc;
ls ~/homeworks/hw_12/genomics/trimmed/*.gz | parallel -j6 "fastqc -t 6 -o . {}"

