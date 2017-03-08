#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define DEGREE(id) (algo_state[2*id])
#define COMMUNITY(id) (algo_state[2*id+1])

int main( int argc, char *argv[] )
{
    /* Argument handling */
    if( argc < 3 )
    {
        printf( "Usage: ./scoda MAX_NODE_ID DEGREE_THRESHOLD IGNORE_LINES < input_graph.txt > output_communities.txt\n");
        printf( "Parameters:\n" );
        printf( "\t-STDIN: tab-separated edge list (each line: SRC_NODE <tab> DST_NODE)\n");
        printf( "\t-STDOUT: community detection result (each line: NODE <tab> COMMUNITY)\n"),
        printf( "\t-MAX_NODE_ID: int32 larger than all nodes IDs in the graph\n" );
        printf( "\t-DEGREE_THRESHOLD: parameter of the algorithm\n" );
        printf( "\t-IGNORE_LINES: number of line to ignore at the beginning of the input file\n" );
        return EXIT_FAILURE;
    }

    /* Parse degree_threshold & max_node_id */
    int32_t degree_threshold, max_node_id, ignore_lines;

    sscanf( argv[1], "%" SCNd32, &max_node_id );
    sscanf( argv[2], "%" SCNd32, &degree_threshold );
    sscanf( argv[3], "%" SCNd32, &ignore_lines );

    /* Memory allocation & initialisation */
    char linebuf[BUFSIZ];
    int32_t *algo_state = (int32_t *) malloc( 2 * max_node_id * sizeof( int32_t ) );
    memset( algo_state, 0, 2 * max_node_id * sizeof( int32_t ) );
    for( int32_t i = 0 ; i < max_node_id ; i++ )
    {
        COMMUNITY( i ) = i;
    }

    /* Waste ignore_lines lines from input stream */
    for( int32_t i = 0 ; i < ignore_lines ; i++ )
    {
        fgets( linebuf, BUFSIZ, stdin );
    }

    /* Main SCoDA loop */
    int32_t src_id, dst_id, src_deg, dst_deg;
    while( fgets( linebuf, BUFSIZ, stdin ) != NULL )
    {
        sscanf( linebuf, "%" SCNd32 "\t%" SCNd32, &src_id, &dst_id );
        src_deg = DEGREE( src_id )++;
        dst_deg = DEGREE( dst_id )++;
        if( src_deg <= degree_threshold && dst_deg <= degree_threshold )
        {
            if( src_deg > dst_deg )
            {
                COMMUNITY( dst_id ) = COMMUNITY( src_id );
            } else {
                COMMUNITY( src_id ) = COMMUNITY( dst_id );
            }
        }
    }
    for( int32_t i = 0 ; i < max_node_id ; i++ )
    {
        if( DEGREE( i ) > 0 )
        {
            printf( "%" PRId32 "\t%" PRId32 "\n", i, COMMUNITY( i ) );
        }
    }
    return EXIT_SUCCESS;
}
