#include "lib/cstd.h"
#include "lib/utils.h"
#include "hw0502.h"

struct option long_options[] = 
{  
    {0, 0, 0, 0},  
};  

int main(int argc, char **argv)
{
    add_help_option(argc, argv);

    bool list_tag_func=0, delete_tag_func=0;

    int32_t c=0,index=0;
    c = getopt_long( argc, argv, "t:T:a:A:y:c:g:ld", long_options, &index );
    if(c=='t')
    {
        CHECK_VALID(argc-3<=10,"Limit number of file amount is 10");
        CHECK_VALID(strlen(optarg)<=30,"The title content is too long");
        for(int i=3; i<argc; i++)
        {
            set_modifier(argv[i]);
            str_copy_(ID3_header.title,optarg);
            save_modifier();
        }
    }
    else if(c=='T')
    {
        CHECK_VALID(argc-3<=10,"Limit number of file amount is 10");
        for(int i=3; i<argc; i++)
        {
            set_modifier(argv[i]);
            int i=0;
            for(i=0;i<strlen(optarg);i++)
            {
                if(optarg[i]<'0'||optarg[i]>'9')
                {
                    i=-1;
                    break;
                }
            }
            int32_t track_value = atoi(optarg);
            if(track_value>255||track_value<0||i==-1) puts("Track value is invalid"); 
            else ID3_header.track = (uint8_t)track_value;
            save_modifier();
        }
    }
    else if(c=='a')
    {
        CHECK_VALID(argc-3<=10,"Limit number of file amount is 10");
        CHECK_VALID(strlen(optarg)<=30,"The artist content is too long");
        for(int i=3; i<argc; i++)
        {
            set_modifier(argv[i]);
            str_copy_(ID3_header.artist,optarg);
            save_modifier();
        }
    }
    else if(c=='A')
    {
        CHECK_VALID(argc-3<=10,"Limit number of file amount is 10");
        CHECK_VALID(strlen(optarg)<=30,"The album content is too long");
        for(int i=3; i<argc; i++)
        {
            set_modifier(argv[i]);
            str_copy_(ID3_header.album,optarg);
            save_modifier();
        }
    }
    else if(c=='y')
    {
        CHECK_VALID(argc-3<=10,"Limit number of file amount is 10");
        CHECK_VALID(strlen(optarg)<=4,"The year value is too big");

        
        for(int i=3; i<argc; i++)
        {
            set_modifier(argv[i]);
            int32_t year_value = atoi(optarg);
            if(year_value==0) puts("Year value is invalid!!");
            else str_copy_(ID3_header.year,optarg);
            save_modifier();
        }
    }
    else if(c=='c')
    {
        CHECK_VALID(argc-3<=10,"Limit number of file amount is 10");
        CHECK_VALID(strlen(optarg)<=28,"The comment content is too long");
        for(int i=3; i<argc; i++)
        {
            set_modifier(argv[i]);
            str_copy_(ID3_header.comment,optarg);
            save_modifier();
        }
    }
    else if(c=='g')
    {
        CHECK_VALID(argc-3<=10,"Limit number of file amount is 10");
        for(int i=3; i<argc; i++)
        {
            set_modifier(argv[i]);
            for(uint8_t i=0; i<144;i++)
            {
                if(is_str_same(genre_table[i],optarg))
                {
                    ID3_header.genre = i;
                    break;
                }
                if(i==144-1)
                {
                    puts("Not found genre number!!");
                }
            }
            save_modifier();
        }
    }
    else if(c=='l')
    {
        CHECK_VALID(argc-2<=10,"Limit number of file amount is 10");
        for(int i=2; i<argc; i++)
        {
            show_list_tag(argv[i]);
        }
    }
    else if(c=='d')
    {
        CHECK_VALID(argc-2<=10,"Limit number of file amount is 10");
        for(int i=2; i<argc; i++)
        {
            delete_tag(argv[i]);
        }
    }
    return 0;
}