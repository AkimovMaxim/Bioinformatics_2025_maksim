#!/bin/bash
#SBATCH --job-name=star
#SBATCH --output=star.out
#SBATCH --error=star.err
#SBATCH --time=04:00:00
#SBATCH --cpus-per-task=34
#SBATCH --partition=medium
#SBATCH --mem=128gb

mkdir -p star_output
mkdir -p star_output/RNA__STARtmp
ulimit -n 10000
STAR --runThreadN 32 \
     --runMode alignReads \
     --genomeDir /projects/mipt_dbmp_biotechnology/GRCh38/ \
     --readFilesIn Erik_mat_CD4_MiLab_S52_R1_001_trimmed.fastq.gz Erik_mat_CD4_MiLab_S52_R2_001_trimmed.fastq.gz \
     --readFilesCommand zcat \
     --outFileNamePrefix star_output/RNA_ \
     --outSAMtype BAM SortedByCoordinate \
     --quantMode GeneCounts \

echo "Alignment Done"
