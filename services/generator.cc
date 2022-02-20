#include <cmath>
#include "node.h"

#include <iostream>
#include <string>
#include <algorithm> // For begin() & end() functions
#include <ctime> // For random numbers
#include <cctype> // For tolower() & toupper()

#include <random>
#include <type_traits>

using namespace std;

// Methods ----->

// Javascript .includes() equivalent
template <class A, class T>
bool Contains(A&& arr, T value){
    return find(begin(arr), end(arr), value) != end(arr);
};
// A function to return a seeded random number generator.
inline std::mt19937& generator() {
    // the generator will only be seeded once (per thread) since it's static
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}

// A function to generate integers in the range [min, max]
template<typename T, typename F>
T rand_int(T min, F max) {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(generator());
}

// Classes
class Letter{

    protected:
    char value;
    int type;

    private:
    char values[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    public:
    friend class Generator;

    Letter(){}

    Letter(char letter){
        this->value = letter;
    }

    enum type{
        vowel = 0,
        consonant = 1
    };

    char Value(){
        return value;
    }
    virtual void SetValue(char newValue){
        this->value = newValue;
    }

    // Generates a random letter
    virtual char GenerateRandom(){
        return values[rand_int(0, 25)];
    }

    virtual char GenerateRandomByFrequency(){
        float probability = rand_int(0, 100000) / 1000.0f;

        if     (probability  <  0.074) return 'z';
        else if (probability <  0.169) return 'q';
        else if (probability <  0.319) return 'x';
        else if (probability <  0.469) return 'j';
        else if (probability <  1.239) return 'k';
        else if (probability <  2.219) return 'v';
        else if (probability <  3.719) return 'b';
        else if (probability <  5.619) return 'p';
        else if (probability <  7.619) return 'y';
        else if (probability <  9.619) return 'g';
        else if (probability < 11.819) return 'f';
        else if (probability < 14.219) return 'w';
        else if (probability < 16.619) return 'm';
        else if (probability < 19.419) return 'c';
        else if (probability < 22.219) return 'u';
        else if (probability < 26.219) return 'l';
        else if (probability < 30.519) return 'd';
        else if (probability < 36.519) return 'r';
        else if (probability < 42.619) return 'h';
        else if (probability < 48.919) return 's';
        else if (probability < 55.619) return 'n';
        else if (probability < 62.619) return 'i';
        else if (probability < 70.119) return 'o';
        else if (probability < 78.319) return 'a';
        else if (probability < 87.419) return 't';
        else if (probability < 100)    return 'e';
        else return '\0';

        /*
        e = 13
        t = 9.1
        a = 8.2
        o = 7.5
        i = 7
        n = 6.7
        s = 6.3
        h = 6.1
        r = 6
        d = 4.3
        l = 4
        u = 2.8
        c = 2.8
        m = 2.4
        w = 2.4
        f = 2.2
        g = 2
        y = 2
        p = 1.9
        b = 1.5
        v = 0.98
        k = 0.77
        j = 0.15
        x = 0.15
        q = 0.095
        z = 0.074 */
    }

    friend Letter GetRandom(){
        Letter random;
        return random;
    }

    friend bool IsLetter(char);
};
// Friend function of Letter class
bool IsLetter(char value){
    Letter letter;
    return Contains(letter.values, tolower(value));
}


class Consonant: public Letter{

    private:
    char values[21] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    char rare_values[3] = {'k', 'x', 'z'};
    char format;

    public:
    Consonant(){
        type = consonant;
        format  = '1';
    }

    char Format(){
        return format;
    }

    virtual void SetValue(char newValue){
        if(Contains(this->values, tolower(newValue)))
            this->value = newValue;
        else{
            cout << "Error: the value '" << newValue << "' is not allowed to be a consonant" << endl;
            throw -1;
        }
    }

    bool CanBeRepeated(){
        
        char scopes[5] = {'f', 'r', 'n', 's', 'z'};

        return Contains(scopes, this->value);
    } 

    char GenerateRandom(){
        
        char random_value = values[rand_int(0, 20)];
        if(Contains(rare_values, random_value))
            random_value = values[rand_int(0, 20)];
        return random_value;
    }
    char GenerateRandomByFrequency(){
        float probability = rand_int(0, 100000) / 1000.0f;

        if      (probability <  0.119) return 'z';
        else if (probability <  0.272) return 'q';
        else if (probability <  0.514) return 'x';
        else if (probability <  0.756) return 'j';
        else if (probability <  1.999) return 'k';
        else if (probability <  3.582) return 'v';
        else if (probability <  6.005) return 'b';
        else if (probability <  9.074) return 'p';
        else if (probability < 12.304) return 'y';
        else if (probability < 15.534) return 'g';
        else if (probability < 19.087) return 'f';
        else if (probability < 22.963) return 'w';
        else if (probability < 26.839) return 'm';
        else if (probability < 31.361) return 'c';
        else if (probability < 37.821) return 'l';
        else if (probability < 44.766) return 'd';
        else if (probability < 54.456) return 'r';
        else if (probability < 64.307) return 'h';
        else if (probability < 74.480) return 's';
        else if (probability < 85.300) return 'n';
        else if (probability < 100)    return 't';
        else return 0;
    }

    friend bool IsConsonant(char);
};
// Friend function of Consonant class
bool IsConsonant(char value){
    Consonant consonant;
    return Contains(consonant.values, tolower(value));
}


class Vowel: public Letter{

    private:
    char values[5] = {'a', 'e', 'i', 'o', 'u'};
    char format;

    public:
    Vowel(){
        type = vowel;
        format = '0';
    }

    char Format(){
        return format;
    }

    virtual void SetValue(char newValue){
        if(Contains(this->values, tolower(newValue)))
            this->value = newValue;
        else{
            cout << "Error: the value '" << newValue << "' is not allowed to be a vowel" << endl;
            throw -1;
        }
    }

    char GenerateRandom(){
        return values[rand_int(0, 4)];
    }

    char GenerateRandomByFrequency(){
        float probability = rand_int(0, 100000) / 1000.0f;

        if      (probability <  7.271) return 'u';
        else if (probability < 25.451) return 'i';
        else if (probability < 44.929) return 'o';
        else if (probability < 66.224) return 'a';
        else if (probability < 100)    return 'e';
        else return 0;
    }

    friend bool IsVowel(char);
    
};
// Friend function of Vowel class
bool IsVowel(char value){
    Vowel vowel;
    return Contains(vowel.values, tolower(value));
}


class Generator{

    public:
    friend class Letter;

    Letter letter;
    Vowel vowel;
    Consonant consonant;

    char letters_to_start[6] = {'a', 'j', 'm', 'c', 'l', 'd'};
    char favorite_letters[11] = {'a', 'e', 'n', 'i', 'l', 'r', 'o', 's', 'h', 'c', 'm'};
    char letters_to_end[5] = {'n', 'e', 'a', 'y', 'l'};

    // Obtains the seed from an string
    std::string GetSeedFormat(std::string name){
        std::string seed_format;
        for (char i : name) {
            if (IsVowel(i))
                seed_format += vowel.Format();
            else if (IsConsonant(i))
                seed_format += consonant.Format();
            else
                seed_format += ' ';
        }
        return seed_format;
    }

    // Generates an string that is the vowel-consonant format of the given string
    std::string GenerateRandomSeed(int length, std::string start_format = std::string()){

        std::string random_seed;

        int vowel_index, consonant_index;
        unsigned int vowels_in_row = 0, consonant_in_row = 0;

        if(start_format.empty()){
            start_format += to_string(rand_int(0, 1));
        }
        random_seed += start_format;

        for(int i = start_format.length() - 1; i < length - 1; i++){

            if(random_seed[i] == vowel.Format()){

                vowel_index = i;
                
                while(random_seed[vowel_index] == vowel.Format()){
                    if(vowel_index >= 0){
                        vowel_index--;
                        vowels_in_row++;
                    }
                }
                int probabilities = rand_int(1, 100);
                switch(vowels_in_row){
                    // If are one vowels in a row
                    case 1:
                        if(probabilities < 70){
                            random_seed += consonant.Format();
                        }
                        else if(probabilities <= 100){
                            random_seed += vowel.Format();
                        }
                        break;
                    // If are two vowels in a row
                    case 2:
                        if(probabilities < 6){
                            random_seed += vowel.Format();
                        }
                        else if(probabilities <= 100){
                            random_seed += consonant.Format();
                        }
                        break;
                    // If are two vowels in a row
                    case 3:
                        random_seed += consonant.Format();
                        break;
                    // More than three vowels in a row
                    default:
                        random_seed += consonant.Format();
                    break;
                }
                
                vowels_in_row = 0; // resetting
            }
            else if(random_seed[i] == consonant.Format()){

                consonant_index = i;
                while(random_seed[consonant_index] == '1'){ // 00
                    if(consonant_index >= 0){
                        consonant_index--;
                        consonant_in_row++;
                    }
                }
                int probabilities = rand_int(1, 100);
                switch(consonant_in_row){
                    // If are one consonant in a row
                    case 1:
                        if(probabilities < 70){
                            random_seed += vowel.Format();
                        }
                        else if(probabilities <= 100){
                            random_seed += consonant.Format();
                        }
                        break;
                    // If are two consonants in a row
                    case 2:
                        if(probabilities < 5){
                            random_seed += consonant.Format();
                        }
                        else if(probabilities <= 100){
                            random_seed += vowel.Format();
                        }
                        break;
                    // If are two consonants in a row
                    case 3:
                        random_seed += vowel.Format();
                        break;
                    default:
                        random_seed += vowel.Format();
                        break;
                }
                consonant_in_row = 0;
            }
            else{
                cout << "Error in Generator::GenerateRandomSeed():" << endl
                     << "Can't recognice '" << random_seed[i] << "' as a valid letter format, (only binaries are accepted)" << endl;
            }
        }
        return random_seed;
    }

    // Here is where the magic happens
    std::string FixedGenerator(int min_length, int max_length, std::string start = std::string()){

        std::string random_name;
        int name_length;
        std::string random_seed;

        name_length = (rand_int(0, max_length - min_length)) + min_length;

        random_seed = GenerateRandomSeed(name_length, GetSeedFormat(start));

        random_name = GenerateRandomNameFromSeed(random_seed);

        if(start.empty()) return random_name;
        else return start + random_name.substr(start.length());
    }

    // Main idea
    std::string GenerateRandomNameFromSeed(std::string seed){

        std::string name_generated;
        int vowels_in_row = 0, consonant_in_row = 0;

        if(seed[0] == vowel.Format()){

            name_generated += vowel.GenerateRandomByFrequency();
            if(!Contains(letters_to_start, name_generated[0]))
                name_generated[0] = vowel.GenerateRandomByFrequency();
        }
        else if(seed[0] == consonant.Format()){

            name_generated += consonant.GenerateRandomByFrequency();
            if(!Contains(letters_to_start, name_generated[0]))
                name_generated[0] = consonant.GenerateRandomByFrequency();
        }

        for(unsigned int i = 1; i < seed.length(); i += 0){
            
            // Vowels
            if(seed[i] == vowel.Format()){
                while(seed[i] == vowel.Format()){
                    i++;
                    vowels_in_row++;
                }
                switch(vowels_in_row){
                    case 1:
                    {
                        char letter_generated = vowel.GenerateRandomByFrequency();

                        if(!Contains(favorite_letters, letter_generated))
                            letter_generated = vowel.GenerateRandomByFrequency();
                        name_generated += letter_generated;
                        break;
                    }
                    case 2:
                    {
                        char letter_generated_1 = '\0', letter_generated_2 = '\0';
                        do{
                            letter_generated_1 = vowel.GenerateRandomByFrequency();
                            letter_generated_2 = vowel.GenerateRandomByFrequency();
                        }
                        while(!(letter_generated_1 != letter_generated_2 || (letter_generated_1 == 'e' && letter_generated_2 == 'e')));

                        name_generated = name_generated + letter_generated_1 + letter_generated_2;
                        break;
                    }
                    case 3:
                    {
                        char letter_generated_1 = '\0', letter_generated_2 = '\0', letter_generated_3 = '\0';
                        do{
                            letter_generated_1 = vowel.GenerateRandomByFrequency();
                            letter_generated_2 = vowel.GenerateRandomByFrequency();
                            letter_generated_3 = vowel.GenerateRandomByFrequency();
                        }
                        while(!((letter_generated_1 != letter_generated_2) && (letter_generated_2 != letter_generated_3) && (letter_generated_1 != letter_generated_3)));

                        name_generated = name_generated + letter_generated_1 + letter_generated_2 + letter_generated_3;
                        break;
                    }
                }
                vowels_in_row = 0;
            }
            // Consonants
            else if(seed[i] == consonant.Format()){
                while(seed[i] == consonant.Format()){
                    i++;
                    consonant_in_row++;
                }
                switch(consonant_in_row){
                    case 1:
                    {
                        char letter_generated = '\0';
                        letter_generated = consonant.GenerateRandomByFrequency();
                        
                        if(!Contains(favorite_letters, letter_generated))
                            letter_generated = consonant.GenerateRandomByFrequency();
                        name_generated += letter_generated;
                        break;
                    }
                    case 2:
                    {
                        char letter_generated_1 = '\0', letter_generated_2 = '\0';
                        do{
                            letter_generated_1 = consonant.GenerateRandomByFrequency();
                            letter_generated_2 = consonant.GenerateRandomByFrequency();
                        }
                        while(!(letter_generated_1 != letter_generated_2));

                        name_generated = name_generated + letter_generated_1 + letter_generated_2;
                        break;
                    }
                    case 3:
                    {
                        char letter_generated_1 = '\0', letter_generated_2 = '\0', letter_generated_3 = '\0';
                        do{
                            letter_generated_1 = consonant.GenerateRandomByFrequency();
                            letter_generated_2 = consonant.GenerateRandomByFrequency();
                            letter_generated_3 = consonant.GenerateRandomByFrequency();
                        }
                        while(!((letter_generated_1 != letter_generated_2) && (letter_generated_2 != letter_generated_3) && (letter_generated_1 != letter_generated_3)));

                        name_generated = name_generated + letter_generated_1 + letter_generated_2 + letter_generated_3;
                        break;
                    }
                }
                consonant_in_row = 0;
            }
            else{
                name_generated += letter.GenerateRandomByFrequency();
            }
        }
        char* end_letter = &name_generated[seed.length() - 1];

        if(IsVowel(*end_letter)){

            if(!Contains(letters_to_end, *end_letter)){
                *end_letter = vowel.GenerateRandomByFrequency();
            }
        }
        else if(IsConsonant(*end_letter)){

            if(!Contains(letters_to_end, *end_letter)){
                *end_letter = consonant.GenerateRandomByFrequency();
            }
        }
        return name_generated;
    }
};

/*
Sources:

Letter frequency: https://en.wikipedia.org/wiki/Letter_frequency
Name letter statistics: https://home.uchicago.edu/~jsfalk/misc/baby_names/
*/

namespace generateName {
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Context;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Number;
    using v8::Value;

    void generateName(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();

        Generator generator;

        // Parsing args[2] as std::string
        String::Utf8Value str(isolate, args[2]);
        std::string start_name(*str);

        // Arguments:
        // [0] min-length, [1] max-length, [2] start-name
        std::string name = generator.FixedGenerator(
            args[0].As<Number>()->Value(),
            args[1].As<Number>()->Value(),
            start_name
        );

        // Parsing data returned from std::string to char array (is required)
        char* name_parsed = const_cast<char*>(name.c_str());

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, name_parsed).ToLocalChecked());
    }

    void generateSeed(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        Generator generator;

        // Arguments:
        // [0] length
        std::string seed = generator.GenerateRandomSeed(args[0].As<Number>()->Value());

        // Parsing data returned from std::string to char array (is required)
        char* seed_parsed = const_cast<char*>(seed.c_str());

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, seed_parsed).ToLocalChecked());
    }

    void generateNameFromSeed(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();
        
        Generator generator;

        // Parsing args[0] as std::string
        String::Utf8Value str(isolate, args[0]);
        std::string given_seed(*str);

        // Arguments:
        // [0] seed
        std::string name = generator.GenerateRandomNameFromSeed(given_seed);

        // Parsing data returned from std::string to char array (is required)
        char* name_parsed = const_cast<char*>(name.c_str());

        cout << "From c++: " << name << endl;

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, name_parsed).ToLocalChecked());
    }

    void getSeedFormat(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();

        Generator generator;

        // Parsing args[0] as std::string
        String::Utf8Value str(isolate, args[0]);
        std::string word(*str);

        // Arguments:
        // [0] seed
        std::string seed = generator.GetSeedFormat(word);

        // Parsing data returned from std::string to char array (is required)
        char* seed_parsed = const_cast<char*>(seed.c_str());

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, seed_parsed).ToLocalChecked());
    }

    void Initialize(Local<Object> exports) {
        // Exporting all methods to Node
        NODE_SET_METHOD(exports, "generateName", generateName);
        NODE_SET_METHOD(exports, "generateSeed", generateSeed);
        NODE_SET_METHOD(exports, "generateNameFromSeed", generateNameFromSeed);
        NODE_SET_METHOD(exports, "getSeedFormat", getSeedFormat);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}