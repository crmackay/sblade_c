


typedef struct alignment_matrices{
	double 	*H;			// H points to the log odds matrix
	int 	*D;			// D points to the direction matrix
	double 	*SL;		// SL points to the P(S|L) matrix
	double 	*SLP;		// SLP points to the P(S|L') matrix
} alignment_matrices;

typedef struct alignment{
	alignment_matrices *M; 	// M is the group of alignments associated with the two sequences
    char	query[100];		// the query of the alignment
    char	subject[100];	// the subject of the alignment
	char	quals[100];		// quals for the query sequence
    char	cigar[10000];	// a cigar representation of the best alignent
} alignment;
