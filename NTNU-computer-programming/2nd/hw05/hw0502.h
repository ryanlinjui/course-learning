#pragma once
#include "lib/cstd.h"

struct
{
    char header[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[28];
    uint8_t zero_byte;
    uint8_t track;
    uint8_t genre;
}ID3_header;


char *genre_table[144]= {
    "Blues","ClassicRock","Country","Dance","Disco","Funk","Grunge","Hip-Hop","Jazz","Metal","NewAge","Oldies","Other","Pop","R&B","Rap","Reggae","Rock","Techno","Industrial",
    "Alternative","Ska","DeathMetal","Pranks","Soundtrack","Euro-Techno","Ambient","Trip-Hop","Vocal","Jazz+Funk","Fusion","Trance","Classical","Instrumental","Acid","House","Game",
    "Gospel","Noise","AlternRock","Bass","Soul","Punk","Space","Meditative","InstrumentalPop",
    "InstrumentalRock","Ethnic","Gothic","Darkwave","Techno-Industrial","Electronic","Pop-Folk","Eurodance","Dream","SouthernRock","Comedy","Cult","Gangsta","Top40","ChristianRap","Pop/Funk","Jungle","NativeAmerican","Cabaret","NewWave","Psychadelic","Rave","Showtunes",
    "Trailer","Lo-Fi","Tribal","AcidPunk","AcidJazz","Polka","Retro","Musical","Rock&Roll",
    "HardRock","Folk","Folk-Rock","NationalFolk","Swing","FastFusion","Bebob","Latin","Revival",
    "Bluegrass","Avantgarde","GothicRock","ProgessiveRock","PsychedelicRock","SymphonicRock",
    "SlowRock","BigBand","Chorus","EasyListening","Acoustic","Humour","Speech","Chanson",
    "ChamberMusic","Sonata","Symphony","BootyBass","Primus","PornGroove","Satire","SlowJam",
    "Tango","Samba","Folklore","Ballad","PowerBallad","RhythmicSoul","Freestyle","Duet","PunkRock","DrumSolo","Acapella","Euro-House","DanceHall","Goa","Drum&Bass","Club-House","Hardcore",
    "Terror","Indie","BritPop","Negerpunk","PolskPunk","Beat","ChristianGangstaRap","HeavyMetal","BlackMetal","Crossover","ContemporaryChristian","ChristianRock","Merengue","Salsa","TrashMeta","Anime","JPop","Synthpop"
};

char *file=NULL;
int32_t fd=0;
uint64_t file_size = 0;
void set_modifier(char *filename)
{
    fd = open( filename, O_RDWR );
    CHECK_VALID(fd!=-1,"Open file error!!");
    
    file = NULL;
    // get fd size start
    struct stat statbuf; 
    if( fstat( fd, &statbuf ) < 0 )
    {
        close( fd );
        puts("fd error!!");
        exit(0);
    } 
    file_size =  statbuf.st_size; 
    // get fd size end
    file = mmap( 0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    memcpy(&ID3_header,file+file_size-sizeof(ID3_header),sizeof(ID3_header));
}

void close_modifier()
{
    close(fd);
}

void save_modifier()
{
    memcpy(file+file_size-sizeof(ID3_header),&ID3_header,sizeof(ID3_header));
    munmap(file,file_size);
    close(fd);
}


void show_list_tag(char *filename)
{
    set_modifier(filename);
    close_modifier();

    printf( "%s:\n",filename);

    printf("    Title: ");
    for(int i=0; i<30&&ID3_header.title[i];i++)
    {
        printf("%c",ID3_header.title[i]);
    }
    printf("\n");

    printf("    Artist: ");
    for(int i=0; i<30&&ID3_header.artist[i];i++)
    {
        printf("%c",ID3_header.artist[i]);
    }
    printf("\n");

    printf("    Album: ");
    for(int i=0; i<30&&ID3_header.album[i];i++)
    {
        printf("%c",ID3_header.album[i]);
    }
    printf("\n");
    
    printf("    Year: ");
    for(int i=0; i<4&&ID3_header.year[i];i++)
    {
        printf("%c",ID3_header.year[i]);
    }
    printf("\n");

    if(ID3_header.genre < 148) printf("    Genre: %s (%hhu)\n",genre_table[ID3_header.genre],ID3_header.genre);
    else printf("    Genre: %s (%hhu)\n","unknown",ID3_header.genre);
    
    printf("    Comment: ");
    for(int i=0; i<28&&ID3_header.comment[i];i++)
    {
        printf("%c",ID3_header.comment[i]);
    }
    printf("\n");

    printf("    Track: %d\n",ID3_header.track);    
}

void delete_tag(char *filename)
{
    set_modifier(filename);
    
    for(int i = 0; i < strlen(ID3_header.header); i++)
    {
        ID3_header.header[i] = 0;
    }

    for(int i = 0; i < strlen(ID3_header.title); i++)
    {
        ID3_header.title[i] = 0;
    }

    for(int i = 0; i < strlen(ID3_header.artist); i++)
    {
        ID3_header.artist[i] = 0;
    }

    for(int i = 0; i < strlen(ID3_header.album); i++)
    {
        ID3_header.album[i] = 0;
    }
    for(int i = 0; i < strlen(ID3_header.year); i++)
    {
        ID3_header.year[i] = 0;
    }
    for(int i = 0; i < strlen(ID3_header.comment); i++)
    {
        ID3_header.comment[i] = 0;
    }
    ID3_header.zero_byte = 0;
    ID3_header.track = 0;
    ID3_header.genre = 255;
    save_modifier();
}