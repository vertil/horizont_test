#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>


struct  compare_nosensetive : public std::binary_function< char,char,bool >
        {
        bool operator () (char x, char y) const
        {
            return toupper( static_cast< unsigned char >(x)) <  toupper( static_cast< unsigned char >(y));
        }
    };

bool less_nosens(const std::string &a, const std::string &b)
    {
        return std::lexicographical_compare( a.begin(),a.end(),
                                             b.begin(),b.end(), compare_nosensetive() );
    }


int main(int argc, char *argv[]) {



    if (argc == 1){

        std::cout<<"no command line arguments, \n"
                   "please set 3 command line arguments:\n"
                   "first - path to txt file,\n"
                   "second - word to delete,\n"
                   "third - new file name\n"
                   "example on windows: horizont_test.exe c:\\test.txt deleteword new_file_name\n"
                   "example on linux: ./horizont_test /user/bin/test.txt deleteword new_file_name"<<std::endl;


        return 0;
    }else if(argc >4){
        std::cout<<"too many command line arguments \n"
                   "please set 3 command line arguments:\n"
                   "first - path to txt file,\n"
                   "second - word to delete,\n"
                   "third - new file name\n"
                   "example on windows: horizont_test.exe c:\\test.txt deleteword new_file_name\n"
                   "example on linux: ./horizont_test /user/bin/test.txt deleteword new_file_name"<<std::endl;
        return 0;
    }

    std::string filepath=argv[1];
    std::string erase_word=argv[2];
    std::string new_file_name=argv[3];

    if (!std::filesystem::exists(filepath)){
        std::cout<<"can't find file "<<filepath<<std::endl;
        return 0;
    }

    std::vector<std::string> file_strings;

    //reading from file
    std::ifstream file(filepath);


    std::string buff;

    while(std::getline(file,buff)){

        int pos = buff.find(erase_word);

        for(;pos!=-1;){

            buff=buff.erase(pos,erase_word.size());

            pos = buff.find(erase_word);
        }

        file_strings.push_back(buff);
    }

    file.close();

    //filtering
    std::sort(file_strings.begin(),file_strings.end(), less_nosens);

    //write to file
    std::ofstream new_file(new_file_name+".txt",std::ios::trunc);

    for(auto i:file_strings){
        new_file << i<<"\n";
    }

    new_file.close();

    std::cout<<"new file - "<<new_file_name+".txt"<<", created in program directory"<<std::endl;

    return 0;
}
