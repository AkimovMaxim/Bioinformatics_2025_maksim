#!/bin/bash
#SBATCH --job-name=fastqc
#SBATCH --output=fastqc.out
#SBATCH --error=fastqc.err
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=4
#SBATCH --mem=8G

mkdir -p fastqc_raw
fastqc -t 4 -o fastqc_raw Erik_mat_CD4_MiLab_S52_R1_001.fastq.gz Erik_mat_CD4_MiLab_S52_R2_001.fastq.gz

cd fastqc_raw
multiqc .
