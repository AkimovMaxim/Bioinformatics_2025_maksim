{
 "cells": [
  {
   "cell_type": "markdown",
   "id": "875eb27b-3741-4232-9aad-994f7aab689d",
   "metadata": {},
   "source": [
    "# 1. Аналоговая реализация алгоритма Нидлмана-Вунша"
   ]
  },
  {
   "cell_type": "markdown",
   "id": "76b4eaf5-b28b-4aad-bc44-da19b61bf0de",
   "metadata": {},
   "source": [
    "## Дано\n",
    "\n",
    "**seq1**: `GACGAAG`\n",
    "\n",
    "**seq2**: `ACCAAG`\n",
    "\n",
    "**Параметры**: Match = 1, Mismatch = -1, Indel = -1 "
   ]
  },
  {
   "cell_type": "markdown",
   "id": "42905856-3ca7-42ff-8c0f-80adbdb967cd",
   "metadata": {},
   "source": [
    "|       | - | **A**  | **C**  | **C**  | **A**  | **A**  |  **G**  |\n",
    "|-------|----|----|----|----|----|----|----|\n",
    "|   -   |  **0** | -1 | -2 | -3 | -4 | -5 | -6 |\n",
    "| **G** | -1 | **-1** | -2 | -3 | -4 | -5 | -4 |\n",
    "| **A** | -2 |  **0** | -1 | -2 | -2 | -3 | -4 |\n",
    "| **C** | -3 | -1 | **1**  |  0 | -1 | -2 | -3 |\n",
    "| **G** | -4 | -2 | 0  | **0** | -1 | -2 | -1 |\n",
    "| **A** | -5 | -3 | -1 | -1 |  **1** | 0  | -1 |\n",
    "| **A** | -6 | -4 | -2 | -2 | 0  | **2**  | -1  |\n",
    "| **G** | -7 | -5 | -3 | -3 | -1  | 1  | **3**  |"
   ]
  },
  {
   "cell_type": "markdown",
   "id": "82184a44-13bc-4828-b610-4e3e1e7b59b1",
   "metadata": {},
   "source": [
    "## Результат выравнивания\n",
    "```\n",
    "seq2: _ A C C A A G\n",
    "        | |   | | |\n",
    "seq1: G A C G A A G\n",
    "```\n",
    "**score = 5 - 1 - 1 = 3**"
   ]
  },
  {
   "cell_type": "markdown",
   "id": "3c90338c-e7ce-45ca-9b7b-8d3cc3e3dd76",
   "metadata": {},
   "source": [
    "# 2. Реализация на питоне алгоритмов Нидлмана-Вунша и Смита-Вотермана"
   ]
  },
  {
   "cell_type": "markdown",
   "id": "710dbc2b-3f95-4856-a403-49d4000e1515",
   "metadata": {},
   "source": [
    "## Алгоритм Нидлмана-Вунша"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 5,
   "id": "5821a794-5319-4e8e-822e-2f39196d5c3d",
   "metadata": {},
   "outputs": [],
   "source": [
    "import numpy as np\n",
    "\n",
    "def needleman_wunsch(seq1, seq2, match, mismatch, indel):\n",
    "    n, m = len(seq1), len(seq2)\n",
    "    matrix = np.zeros((n+1, m+1), dtype=int)\n",
    "    \n",
    "    for i in range(1, n+1):\n",
    "        matrix[i][0] = matrix[i-1][0] + indel\n",
    "    for j in range(1, m+1):\n",
    "        matrix[0][j] = matrix[0][j-1] + indel\n",
    "    \n",
    "    for i in range(1, n+1):\n",
    "        for j in range(1, m+1):\n",
    "            match_score = matrix[i-1][j-1] + (match if seq1[i-1] == seq2[j-1] else mismatch)\n",
    "            delete = matrix[i-1][j] + indel\n",
    "            insert = matrix[i][j-1] + indel\n",
    "            matrix[i][j] = max(match_score, delete, insert)\n",
    "    print(matrix)\n",
    "    align1, align2 = [], []\n",
    "    i, j = n, m\n",
    "    while i > 0 or j > 0:\n",
    "        if i > 0 and j > 0 and matrix[i][j] == matrix[i-1][j-1] + (match if seq1[i-1] == seq2[j-1] else mismatch):\n",
    "            align1.append(seq1[i-1])\n",
    "            align2.append(seq2[j-1])\n",
    "            i -= 1\n",
    "            j -= 1\n",
    "        elif i > 0 and matrix[i][j] == matrix[i-1][j] + indel:\n",
    "            align1.append(seq1[i-1])\n",
    "            align2.append('-')\n",
    "            i -= 1\n",
    "        else:\n",
    "            align1.append('-')\n",
    "            align2.append(seq2[j-1])\n",
    "            j -= 1\n",
    "\n",
    "    return matrix[n][m], ''.join(reversed(align1)), ''.join(reversed(align2))"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 19,
   "id": "66fbce2f-e9a9-4139-a342-b1976f7fad1d",
   "metadata": {},
   "outputs": [
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "[[ 0 -1 -2 -3 -4 -5 -6]\n",
      " [-1 -1 -2 -3 -4 -5 -4]\n",
      " [-2  0 -1 -2 -2 -3 -4]\n",
      " [-3 -1  1  0 -1 -2 -3]\n",
      " [-4 -2  0  0 -1 -2 -1]\n",
      " [-5 -3 -1 -1  1  0 -1]\n",
      " [-6 -4 -2 -2  0  2  1]\n",
      " [-7 -5 -3 -3 -1  1  3]]\n",
      "Выравнивание:\n",
      "GACGAAG\n",
      "-ACCAAG\n",
      "Score = 3\n"
     ]
    }
   ],
   "source": [
    "score, align1, align2 = needleman_wunsch(seq1 = \"GACGAAG\", seq2 = \"ACCAAG\", match = 1, mismatch = -1, indel = -1)\n",
    "print('Выравнивание:')\n",
    "print(align1)\n",
    "print(align2)\n",
    "print(f'Score = {score}')"
   ]
  },
  {
   "cell_type": "markdown",
   "id": "7d6c2425-3f8b-4de6-a8e3-832a3029ed27",
   "metadata": {},
   "source": [
    "## Алгоритм Смита-Вотермана"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 6,
   "id": "d1aab797-ab9d-4715-a96d-90ce4a1144f1",
   "metadata": {},
   "outputs": [
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "Матрица очков:\n",
      "[[ 0  0  0  0  0  0  0]\n",
      " [ 0 -1 -1 -1 -1 -1  1]\n",
      " [ 0  1  0 -1  0  0  0]\n",
      " [ 0  0  2  1  0 -1 -1]\n",
      " [ 0 -1  1  1  0 -1  0]\n",
      " [ 0  1  0  0  2  1  0]\n",
      " [ 0  1  0 -1  1  3  2]\n",
      " [ 0  0  0 -1  0  2  4]]\n",
      "\n",
      "Выравнивание:\n",
      "ACGAAG\n",
      "ACCAAG\n",
      "\n",
      "Счет: 4\n"
     ]
    }
   ],
   "source": [
    "def smith_waterman(seq1, seq2, match_score=1, mismatch_penalty=-1, gap_penalty=-1):\n",
    "    \n",
    "    m, n = len(seq1), len(seq2)\n",
    "    \n",
    "    H = np.zeros((m + 1, n + 1), dtype=int)\n",
    "\n",
    "    max_score = 0\n",
    "    max_pos = (0, 0)\n",
    "    \n",
    "    for i in range(1, m + 1):\n",
    "        for j in range(1, n + 1):\n",
    "            match = H[i - 1, j - 1] + (match_score if seq1[i - 1] == seq2[j - 1] else mismatch_penalty)\n",
    "            delete = H[i - 1, j] + gap_penalty\n",
    "            insert = H[i, j - 1] + gap_penalty\n",
    "            H[i, j] = max(match, delete, insert)  \n",
    "            \n",
    "            if H[i, j] > max_score:\n",
    "                max_score = H[i, j]\n",
    "                max_pos = (i, j)\n",
    "    \n",
    "    aligned_seq1 = []\n",
    "    aligned_seq2 = []\n",
    "    i, j = max_pos\n",
    "    \n",
    "    while i > 0 and j > 0:\n",
    "        if H[i, j] == H[i - 1, j - 1] + (match_score if seq1[i - 1] == seq2[j - 1] else mismatch_penalty):\n",
    "            aligned_seq1.append(seq1[i - 1])\n",
    "            aligned_seq2.append(seq2[j - 1])\n",
    "            i -= 1\n",
    "            j -= 1\n",
    "        elif H[i, j] == H[i - 1, j] + gap_penalty:\n",
    "            aligned_seq1.append(seq1[i - 1])\n",
    "            aligned_seq2.append('-')\n",
    "            i -= 1\n",
    "        else:\n",
    "            aligned_seq1.append('-')\n",
    "            aligned_seq2.append(seq2[j - 1])\n",
    "            j -= 1\n",
    "    \n",
    "    aligned_seq1.reverse()\n",
    "    aligned_seq2.reverse()\n",
    "    \n",
    "    return H, \"\".join(aligned_seq1), \"\".join(aligned_seq2), max_score\n",
    "\n",
    "seq1 = \"GACGAAG\"\n",
    "seq2 = \"ACCAAG\"\n",
    "\n",
    "H, align1, align2, score = smith_waterman(seq1, seq2)\n",
    "\n",
    "print(\"Матрица очков:\")\n",
    "print(H)\n",
    "print(\"\\nВыравнивание:\")\n",
    "print(align1)\n",
    "print(align2)\n",
    "print(\"\\nСчет:\", score)\n"
   ]
  },
  {
   "cell_type": "markdown",
   "id": "0e148066-d286-4d24-a9ff-e2dca0b99ca8",
   "metadata": {},
   "source": [
    "# 3. Библиотеки Python"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 1,
   "id": "ebff8c13-7fba-45a7-adfd-817892fb89da",
   "metadata": {},
   "outputs": [
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "Requirement already satisfied: biopython in /home/makimov/.conda/envs/python_main/lib/python3.12/site-packages (1.85)\n",
      "Requirement already satisfied: numpy in /home/makimov/.conda/envs/python_main/lib/python3.12/site-packages (from biopython) (1.26.4)\n",
      "Note: you may need to restart the kernel to use updated packages.\n"
     ]
    }
   ],
   "source": [
    "pip install biopython"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 7,
   "id": "6c2305ce-8898-4153-8f55-98e4d8012bab",
   "metadata": {},
   "outputs": [
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "GACGAAG\n",
      " ||.|||\n",
      "-ACCAAG\n",
      "  Score=3\n",
      "\n"
     ]
    }
   ],
   "source": [
    "from Bio import pairwise2\n",
    "alignments = pairwise2.align.globalms(\"GACGAAG\", \"ACCAAG\", 1, -1, -1, -1)\n",
    "print(pairwise2.format_alignment(*alignments[0]))"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 3,
   "id": "902742a1-00eb-4e25-a3de-b08509720c8a",
   "metadata": {},
   "outputs": [
    {
     "name": "stdout",
     "output_type": "stream",
     "text": [
      "2 ACGAAG\n",
      "  ||.|||\n",
      "1 ACCAAG\n",
      "  Score=4\n",
      "\n"
     ]
    }
   ],
   "source": [
    "alignments = pairwise2.align.localms(\"GACGAAG\", \"ACCAAG\", 1, -1, -1, -1)\n",
    "print(pairwise2.format_alignment(*alignments[0]))"
   ]
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Python 3 (ipykernel)",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.12.9"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 5
}
