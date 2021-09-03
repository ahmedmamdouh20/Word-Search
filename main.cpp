#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
const int N=10;
string s[]= {"world","task","name","cup","share","complete","global","comment"};
char arr[N][N];
int sSize = sizeof(arr) / sizeof(arr[0]);

void intialize() // fill empty 2d array with
{
    for(int x=0; x<N; x++)
    {
        for(int y=0; y<N; y++)
        {
            arr[x][y]='_';
        }
    }
}

void set_arr_horiz(int ix,int iy,int fx,int fy,string sa) // set string char by char horizontal by increment j only and i still fixed
{
    int k=0;
    for(int j=iy; j<fy+1; j++)  // 0 0 -- 0 1 -- 0 2 -- 0 3 -- 0 4
    {
        arr[ix][j]=sa[k];
        k++;
    }
}
void set_arr_vert(int ix,int iy,int fx,int fy,string sa) // set string char by char  vertical by increment i only and j still fixed
{
    int k=0;
    for(int j=ix; j<fx+1; j++) // 0 0 -- 1 0 -- 2 0 -- 3 0-- 4 0
    {
        arr[j][iy]=sa[k];
        k++;
    }
}
void set_arr_diagonal(int ix,int iy,int fx,int fy,string sa) // set string diagonal char by char by increment i and j
{
    int k=0;
    for(int i=ix; i<fx+1; i++)
    {
        for(int j=iy; j<fy+1; j++) // 0 0 -- 1 1 -- 2 2 -- 3 3 -- 4 4
        {
            arr[i][j]=sa[k];
            k++;
            i++;
        }
    }
}
void set_random_char() // function to set random char in empty spaces after fill words in 2d array
{
    int r=0;
    char c;
    for(int x=0; x<10; x++)
    {
        for(int y=0; y<10; y++)
        {
            if(arr[x][y]=='_')
            {
                r= rand() % 26;        // generate a random number
                c= 'a' + r;            // Convert to a character from a-z
                arr[x][y]=c;

            }
        }
    }
}
void intialize_grid()
{
    intialize();
    int rand_num;
    int len;
    int counter=0;
    int intialX,intialY,finalX,finalY;
    int random[]= {0,0,0,0,1,1,2,2}; // array of random number which 0 for horiz and 1 for vertic and 2 for diagonal
    for(int i=0; i<8; i++) // loop iterate over array of string
    {
        intialX=0;
        intialY=0;
        finalX=0;
        finalY=0;
        counter=0;
        srand(time(0));
        random_shuffle(random,random+8);
        if(random[i]==0)
        {
            for(int x=0; x<N; x++)
            {


                for(int y=0; y<N; y++)
                {

                    len=s[i].size();
                    if(arr[x][y]=='_')
                    {
                        counter++;
                    }
                    if(counter==1) // to take first index will fill first char of string
                    {
                        intialX=x;
                        intialY=y;
                    }
                     if(arr[x][y]!='_'){ // to avoid overwrite and update counter if found empty space and next not empty in same row
                        counter=0;
                    }




                    if(counter==len) // if counter == len string break from inner  loop
                    {
                        finalY=y;
                        break;
                    }

                }
                if(counter==len) //if counter == len string break from outer  loop
                {
                    finalX=x;
                    break;
                }
                counter=0; // update counter in case there 3 space in last row and strong is 5 char so cant store 2 here and 3 in  other row
            }
            set_arr_horiz(intialX,intialY,finalX,finalY,s[i]); // call function to set char from arr[ix][iy] to arr[fx][fy]
        }
        else if(random[i]==1)
        {
            for(int x=0; x<N; x++)
            {


                for(int y=0; y<N; y++)
                {

                    len=s[i].size();
                    if(arr[y][x]=='_')
                    {
                        counter++;
                    }
                    if(counter==1)
                    {
                        intialX=x;
                        intialY=y;
                    }
                     if(arr[x][y]!='_'){
                        counter=0;
                    }




                    if(counter==len)
                    {
                        finalY=y;
                        break;
                    }

                }
                if(counter==len)
                {
                    finalX=x;
                    break;
                }
                counter=0;

            }
            set_arr_vert(intialY,intialX,finalY,finalX,s[i]);
        }
        else
        {
            int index;
            for(int x=0; x<N; x++)
            {

                index=x;
                for(int y=0; x<N; y++)
                {
                    if(arr[x][y]=='_')
                    {
                        counter++;
                    }
                    len=s[i].size();
                    if(counter==1)
                    {
                        intialX=x;
                        intialY=y;
                    }
                    if(arr[x][y]!='_'){
                        counter=0;
                    }
                    x++;


                    if(counter==len)
                    {
                        finalY=y;
                        break;
                    }

                }

                if(counter==len)
                {
                    finalX=x-1;
                    break;
                }
                counter=0;
                x=index;
            }
            set_arr_diagonal(intialX,intialY,finalX,finalY,s[i]);
        }

    }
    set_random_char(); // iterate over grid and fill empty with random char
}
void search_word(string word)
{
    int k=0;
    bool found=false;
    int len=word.size();
    int intialX,intialY,finalX,finalY;

    for(int x=0; x<N; x++)
    {


        for(int y=0; y<N; y++)
        {

            if(arr[x][y]==word[k])
            {
                k++;

            }
            if(k==1)
            {
                intialX=x;
                intialY=y;
            }

            if(k==len)
            {
                finalY=y;
                break;
            }

        }
        if(k==len)
        {
            finalX=x;
            found=true;
            break;
        }
        k=0;

    }
    if(found)
    {
        for(int x=intialY; x<finalY+1; x++)
        {
            arr[intialX][x]='*';
        }
    }
    if(!found)
    {

        for(int x=0; x<N; x++)
        {


            for(int y=0; y<N; y++)
            {

                if(arr[y][x]==word[k])
                {
                    k++;
                }
                if(k==1)
                {
                    intialX=x;
                    intialY=y;
                }
                if(k==len)
                {
                    finalY=y;
                    break;
                }

            }
            if(k==len)
            {
                finalX=x;
                found=true;
                break;
            }
            k=0;
        }
        if(found)
        {
            for(int x=intialY; x<finalY+1; x++) // 0 0 2 0
            {
                arr[x][intialX]='*';
            }
        }




    }
    if(!found){
         int index;
            for(int x=0; x<N; x++)
            {

                index=x;
                for(int y=0; x<N; y++)
                {
                    if(arr[x][y]==word[k])
                    {
                        k++;
                    }
                    if(k==1)
                    {
                        intialX=x;
                        intialY=y;
                    }
                    x++;


                    if(k==len)
                    {
                        finalY=y;
                        break;
                    }

                }

                if(k==len)
                {
                    finalX=x-1;
                    found=true;
                    break;
                }
                k=0;
                x=index;
            }
        for(int i=intialX; i<finalX+1; i++)
        {
            for(int j=intialY; j<finalY+1; j++) // 0 0 -- 1 1 -- 2 2 -- 3 3 -- 4 4
            {
                arr[i][j]='*';
                i++;
            }
        }
    }


}

void print_grid()
{
    for(int x=0; x<10; x++)
    {
        for(int y=0; y<10; y++)
        {
            cout<<arr[x][y]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

}
void input_guess()
{
    int counter=0;
    char ans;
    string word;
    bool searchh=false;
    while(ans!='n')
    {
        cout<<"Enter your guess :";
        cin>>word;
            for(int i=0; i<sSize; i++)
            {
                if (word == s[i])  // check if word in array of string so score increment by 1
                {
                    counter++;
                    search_word(word);
                    break;
                }

            }
              print_grid();
              cout<<"Are any guess another Y/N"<<endl;
              cin>>ans;
    }

    if(counter ==8)
    {
        cout<<"Congratulation you Won by score:"<<counter<<" out 8"<<endl;

    }
    else
    {
        cout<<"Good your Score is "<<counter<<" out 8"<<endl;
    }

}

void grid_clear(){
     for(int x=0; x<10; x++)
    {
        for(int y=0; y<10; y++)
        {
            arr[x][y]<<'_';
        }
    }
}
void play_game(){
     char a;
     while(a!='n'){
     intialize_grid();
     print_grid();
     input_guess();
     cout<<"Do you want to play again y/n"<<endl;
     cin>>a;
     grid_clear();
     }

}
int main()
{
    cout<<"---------------------Welcome to Word Search-----------------------"<<endl;
    play_game();
    cout<<"Thanks for playing our game";
    return 0;
}
