#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>  // remove?


/*
1.)Extract essential details(age, sex, species, color, weight) from arrivingAnimals.txt.
2.)Calculate birthdays based on the provided data.
3.)Utilize animalNames.txt to assign unique names to each animal.
4.)Generate a unique ID for every animal, symbolizing their species and a sequential number.
5.)Strategically organize animals into their respective habitats(you will have four classes named - hyena, line, tiger, and bear(sub classes of Animal).
6.)Compile a detailed report(zooPopulation.txt) showcasing the organized zoo population, complete with names, attributes, and habitat information.

*/









using namespace std;

struct Animal
{
    int ID;
    string name;
    string age;
    string sex;
    string breed;
    string birthseason;
    string color;
    string weight;
    string origin;
    string country;
    string birthday;
};



void longLine()
{
    cout << "*******************************" << endl;
}



//Derive an animal's birthday from the data. Use ISO 8601 format for dates. Adapt your logic for cases where the birth season is not provided.
//birth date 2018-03-15
string genBirthday(string age, string birthseason)
{
    // Get the current time (seconds since epoch)
    std::time_t t = std::time(0);  // Get current time
    std::tm now;  // Create a tm struct to hold the local time

    // Use localtime_s instead of localtime
    localtime_s(&now, &t);  // Convert it to local time securely

    // Extract the year and month from the tm struct
    int year = now.tm_year + 1900;  // tm_year is the number of years since 1900
    int month = now.tm_mon + 1;     // tm_mon is the month (0-11), so add 1 to get 1-12

    string birthday;
    string birthMonth = "unknown";
    int ageInt = std::stoi(age);
    int birthYearInt = (year - ageInt);
    std::string birthYearStr = std::to_string(birthYearInt);


    if (birthseason == "spring ")
    {
        //cout << "**SPRING**" << "\n";
        birthMonth = "March";
        
    }
    if (birthseason == "summer ")
    {
        birthMonth = "June";
    }
    if (birthseason == "fall ")
    {
        birthMonth = "August";
    }
    if (birthseason == "winter ")
    {
        birthMonth = "November";
    }

    else
    {
      //birthday = "unknown birthday";
    }
    birthday = birthMonth + " " + birthYearStr;
    return birthday;
}




// Helper function to trim whitespace from strings
string trim(const string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}


int main()
{

    ifstream MyFile;

    // Open arrivingAnimals.txt for reading
    MyFile.open("arrivingAnimals.txt", ios::in); // read mode

    if (!MyFile.is_open())
    {
        cout << "Unable to open file!" << endl;
        return 1; // Exit the program if the file is not found
    }

    const int MAX_ANIMALS = 100; // Maximum number of animals
    Animal animal[MAX_ANIMALS];  // Array to hold data for animals
    int count = 1;               // Counter to track whether the line is even or odd
    int lineCount = 0;           // Line counter for tracking the line number

    string line;
    string buffer;  // Used as a placeholder for skipping values

    // Read each line from the file
    while (getline(MyFile, line))
    {
        // Ensure that we do not exceed the array size
        if (lineCount >= MAX_ANIMALS)
        {
            cout << "Maximum number of animals reached." << endl;
            break;  // Stop processing if we've hit the limit
        }


        // Split the line by commas
        istringstream stream(line);
        string token;
        vector<string> tokens;

        int loopCount = 0;

        // Read each token (part between commas) and store in the vector
        while (getline(stream, token, ','))
        {
            // Trim spaces from the token before adding to vector
            // Pretty sure I added this whitespace right back
            token = trim(token);

          
            if (count == 1)
            {
                

                if (loopCount == 0)
                {
                    istringstream stream1(token);
                    getline(stream1, token, ' ');
                    animal[lineCount].age += token + " ";
                    getline(stream1, token, ' ');
                    token + " ";
                    getline(stream1, token, ' ');
                    token + " ";
                    getline(stream1, token, ' ');
                    animal[lineCount].sex += token + " ";
                    token + " ";
                    getline(stream1, token, ' ');
                    animal[lineCount].breed += token + " ";
                }

                if (loopCount == 1)
                {
                    istringstream stream1(token);
                    getline(stream1, token, ' ');
                    token + " ";
                    getline(stream1, token, ' ');
                    token + " ";
                    getline(stream1, token, ' ');
                    token + " ";
                    animal[lineCount].birthseason += token + " ";
                }

                if (loopCount == 2)
                {
                    istringstream stream1(token);
                    getline(stream1, token, ' ');
                    animal[lineCount].color += token + " ";
                }

                if (loopCount == 3)
                {
                    istringstream stream1(token);
                    getline(stream1, token, ' ');
                    animal[lineCount].weight += token + " ";
                }

                if (loopCount == 4)
                {
                    animal[lineCount].origin += token;
                    
                }

            }

            //because the last word was on a separate line, it gets picked up here on second scan
            if (count == 2)
            {
                animal[lineCount].country = token;
            }

            
            //assign unique animal ID's
            animal[lineCount].ID = lineCount;
            ++loopCount;

        }

        

        // Increment the count to alternate between odd and even rows
        ++count;

        if (count == 2)
        {
            ++lineCount;
            
        }

        // If count reaches 3, reset it back to 1 for the next animal cycle
        if (count == 3)
        {
            // Reset count to 1 to start the next animal's data
            count = 1; 
         
        }

    }

    MyFile.close();  // Close the file after reading

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ifstream file("animalNames.txt");

    // Check if the file is open successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    
    //std::string line;
    std::vector<std::string> hyenaNames, lionNames, bearNames, tigerNames;
    std::string currentCategory;

    // Read the file line by line
    while (std::getline(file, line)) {
        // Trim leading and trailing spaces (if any)
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Check for category names and set current category
        if (line == "Hyena Names:") 
        {
            currentCategory = "Hyena";
        }
        else if (line == "Lion Names:")
        {
            currentCategory = "Lion";
        }
        else if (line == "Bear Names:") 
        {
            currentCategory = "Bear";
        }
        else if (line == "Tiger names:") 
        {
            currentCategory = "Tiger";
        }
        else {
            // Process names if we are in a valid category
            if (currentCategory == "Hyena" || currentCategory == "Lion" || currentCategory == "Bear" || currentCategory == "Tiger") 
            {
                // Split the line into names using a stringstream
                std::stringstream ss(line);
                std::string name;

                // Extract names separated by commas and store them in the appropriate vector
                while (std::getline(ss, name, ',')) {
                    // Remove any leading/trailing spaces from each name
                    name.erase(0, name.find_first_not_of(" \t"));
                    name.erase(name.find_last_not_of(" \t") + 1);

                    // Store the name in the corresponding category
                    if (currentCategory == "Hyena") 
                    {
                        hyenaNames.push_back(name);
                    }
                    else if (currentCategory == "Lion") 
                    {
                        lionNames.push_back(name);
                    }
                    else if (currentCategory == "Bear") 
                    {
                        bearNames.push_back(name);
                    }
                    else if (currentCategory == "Tiger") 
                    {
                        tigerNames.push_back(name);
                    }
                }
            }
        }
    }

    // Close the file
    file.close();

    

    cout << endl;
    longLine();
    cout << endl;
    
   
    ////////////////////////////////////////////////////////////////////////////////////

    int i = 0;
    int hyena = 0, lion = 0, tiger = 0, bear = 0;
    while (i < 16)
    {
        
        

       // cout << " breed read = " << animal[i].breed << endl;

        if (animal[i].breed == "hyena ")
        {
            animal[i].name = hyenaNames[hyena];
            ++hyena;
        }

        if (animal[i].breed == "lion ")
        {
            animal[i].name = lionNames[lion];
            ++lion;
        }

        if (animal[i].breed == "tiger ")
        {
            animal[i].name = tigerNames[tiger];
            ++tiger;
        }

        if (animal[i].breed == "bear ")
        {
            animal[i].name = bearNames[bear];
            ++bear;
        }
        //else
       // {
           // cout << " no more roomfor animals exist."
        //}
        ++i;
    }


    // Create an ofstream object to write to a file
    ofstream zooReport("zooPopulation.txt");

    // Check if the file opened successfully
    if (!zooReport) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Output the details of the animals stored in the array
    //for (int i = 0; i < lineCount; ++i)
    for (int i = 0; i < 16; ++i)
    {
        //cout << "\nAnimal #" << i  << "\n";
        cout << endl;
        longLine();
        zooReport << "***********************************" << endl;
        cout << endl;
        cout << "Animal ID # " << animal[i].ID << endl;
        zooReport << "Animal ID # " << animal[i].ID << endl;
        cout << "Name = " << animal[i].name << endl;;
        zooReport << "Name = " << animal[i].name << endl;;
        cout << "Age = " << animal[i].age << endl;
        zooReport << "Age = " << animal[i].age << endl;
        cout << "Gender = " << animal[i].sex << endl;
        zooReport << "Gender = " << animal[i].sex << endl;
        cout << "Breed = " << animal[i].breed << endl;
        zooReport << "Breed = " << animal[i].breed << endl;
        cout << "Birthseason = " << animal[i].birthseason << endl;
        zooReport << "Birthseason = " << animal[i].birthseason << endl;
        cout << "Color = " << animal[i].color << endl;
        zooReport << "Color = " << animal[i].color << endl;
        cout << "Weight = " << animal[i].weight << endl;
        zooReport << "Weight = " << animal[i].weight << endl;
        cout << "Origin = " << animal[i].origin << endl;
        zooReport << "Origin = " << animal[i].origin << endl;
        cout << "Nationality = " << animal[i].country << endl;
        zooReport << "Nationality = " << animal[i].country << endl;
        cout << "Birthday = " << genBirthday(animal[i].age, animal[i].birthseason) << "\n";
        zooReport << "Birthday = " << genBirthday(animal[i].age, animal[i].birthseason) << "\n";
        cout << "Habitat = " << animal[i].breed << "enclosure." << endl;
        zooReport << "Habitat = " << animal[i].breed << "enclosure." << endl;
       
    }

    std::cout << endl;


    

    

    // Write data to the file
    
    //zooReport << "C++ makes file handling easy!" << endl;

    // Close the file
    zooReport.close();

    cout << "Data has been written to output.txt" << endl;





    return 0;
}
