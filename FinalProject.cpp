#include <iostream>
#include "Graph.h"
#include "ConsoleUtils.h"
#include"string"
#include <iostream>
#include <cstdlib>
using namespace std;



int main()
{
    bool app = true;
    Graph::UserNode* test = new Graph::UserNode(); // Assuming UserNode includes methods login() and signup()
    Graph::UserNode* u = nullptr;
    Graph::UserNode user1("Adham", "Walid", "adhamwalid", "password123", false, "123 Cairo St", "01012345678");
    Graph::UserNode user2("Yehya", "AlAbyad", "yehyaalabyad", "mypassword", true, "456 Alexandria St", "01098765432");
    Graph::UserNode user3("Nouran", "Mohamed", "nouranmohamed", "securepass", false, "789 Luxor St", "01255512345");
    Graph::UserNode user4("Reetaj", "Ahmed", "reetajahmed", "password456", true, "101 Giza St", "01122233344");
    Graph::UserNode user5("Mohamed", "Wael", "mohamedwael", "password789", false, "202 Aswan St", "01133344455");
    Graph::UserNode user6("Carol", "Kamal", "carolkamal", "password101", true, "303 Sharm El Sheikh St", "01244455566");
    Graph::UserNode user7("Hassan", "Ismail", "hassanismail", "password112", false, "404 Hurghada St", "01555566677");
    Graph::UserNode user8("Eslam", "Fawzy", "eslamfawzy", "password131", true, "505 Tanta St", "01166677788");
    Graph::UserNode user9("Abdo", "Adel", "abdoadel", "password145", false, "606 Suez St", "01077788899");
    Graph::UserNode user10("Omar", "Ashraf", "omarashraf", "password159", true, "707 Cairo St", "01288899900");
    Graph::UserNode user11("Jana", "Hasheesh", "janahasheesh", "password167", false, "808 Zagazig St", "01599900011");
    Graph::UserNode user12("Toka", "ElSayed", "tokaelsayed", "password178", true, "909 Alexandria St", "01200011122");
    Graph::UserNode user13("Amir", "Tamer", "amirtamer", "password189", false, "1010 Sohag St", "01011122233");
    Graph::UserNode user14("Moaz", "Ahmed", "moazahmed", "password198", true, "1111 Fayoum St", "01122233344");
    Graph::UserNode user15("Mohamed", "Badra", "mohamedbadra", "password201", false, "1212 Ismailia St", "01233344455");
    Graph::UserNode user16("Ahmed", "Salama", "ahmedsalama", "password213", false, "123 Mansoura St", "01512323434");
    Graph::UserNode user17("Ashraf", "Abdelraouf", "prof.ashrafabdelraouf", "mypassword321", true, "456 Cairo St", "01123434545");
    Graph::UserNode user18("Tamer", "Hagras", "tamerhagras", "securepass112", false, "789 Alexandria St", "01234545656");
    Graph::UserNode user19("Tyler", "Durden", "tylerdurden", "password444", true, "101 Giza St", "01545656767");
    Graph::UserNode user20("Arthur", "Morgan", "arthurmorgan", "password555", false, "202 Luxor St", "01056767878");
    Graph::UserNode user21("Nasser", "Eldesouky", "nassereldesouky", "mypassword777", true, "303 Aswan St", "01267878989");
    Graph::UserNode user22("Gaafar", "Elomda", "gaafarelomda", "securepass888", false, "404 Hurghada St", "01178989090");
    Graph::UserNode user23("Omar", "Raeia", "omaraeia", "password999", true, "505 Sharm El Sheikh St", "01589090101");
    Graph::UserNode user24("Tyler", "Durden", "theNarrator", "password000", false, "606 Giza St", "01090101212");
    Graph::UserNode user25("Ryan", "Gosling", "ryangosling", "mypassword202", true, "707 Cairo St", "01101212323");
    Graph::UserNode user26("Hamada", "Helal", "hamadahelal", "securepass333", false, "808 Alexandria St", "01212323434");
    Graph::UserNode user27("Ahmed", "Alsayed", "ahmedalsayed", "password444", true, "909 Luxor St", "01523434545");
    Graph::UserNode user28("Hassan", "Hazem", "hassanhazem", "mypassword555", false, "1010 Aswan St", "01034545656");
    Graph::UserNode user29("Mostafa", "Amr", "mostafaamr", "securepass666", true, "1111 Hurghada St", "01245656767");
    Graph::UserNode user30("Mariam", "Shemis", "mariamshemis", "password777", false, "1212 Sharm El Sheikh St", "01156767878");
    Graph::UserNode user31("Abdelrahman", "Zayed", "abdelrahmanzayed", "mypassword888", true, "1313 Cairo St", "01567878989");
    Graph::UserNode user32("Mariam", "Tarek", "mariamtarek", "securepass999", false, "1414 Alexandria St", "01078989090");
    Graph::UserNode user33("Mariam", "Ibrahim", "mariamibrahim", "password000", true, "1515 Luxor St", "01289090101");
    Graph::UserNode user34("Hossam", "Osama", "hossamosama", "mypassword111", false, "1616 Aswan St", "01190101212");
    Graph::UserNode user35("Omar", "Abouraia", "omarabouraia", "securepass222", true, "1717 Hurghada St", "01501212323");
    Graph::UserNode user36("Aly", "Attia", "alyattia", "password333", false, "1818 Giza St", "01012323434");
    Graph::UserNode user37("Saeed", "Negm", "saeednegm", "mypassword444", true, "1919 Cairo St", "01223434545");
    Graph::UserNode user38("Zeina", "Maged", "zeinamaged", "password123", false, "123 Cairo St", "01223434545");
    Graph::UserNode user39("Sagda", "Mansour", "sagdamansour", "mypassword234", true, "456 Alexandria St", "01534545656");
    Graph::UserNode user40("Jana", "Mohamed", "janamohamed", "securepass345", false, "789 Luxor St", "01045656767");
    Graph::UserNode user41("Jana", "Khaled", "janakhaled", "password456", true, "101 Aswan St", "01156767878");
    Graph::UserNode user42("Rahaf", "Ahmed", "rahafahmed", "mypassword567", false, "202 Hurghada St", "01567878989");
    Graph::UserNode user43("David", "Sameh", "davidsameh", "securepass678", true, "303 Sharm El Sheikh St", "01078989090");
    Graph::UserNode user44("Youssef", "Salem", "youssefsalem", "password789", false, "404 Cairo St", "01289090101");
    Graph::UserNode user45("Ashraf", "Sameh", "ashrafsameh", "mypassword890", true, "505 Alexandria St", "01190101212");
    Graph::UserNode user46("Adham", "Elattar", "adhamelattar", "securepass123", false, "606 Luxor St", "01501212323");
    Graph::UserNode user47("Zein", "Kazem", "zeinkazem", "password234", true, "707 Aswan St", "01012323434");
    Graph::UserNode user48("Aly", "Omar", "alyomar", "mypassword345", false, "808 Hurghada St", "01223434545");



    //user1.accept(user2);


    user3.accept(user4);
    user4.accept(user8);

    user1.accept(user3);
    user1.accept(user2);
    user5.accept(user2);
    user1.accept(user8);
    user5.accept(user8);
    user42.accept(user7);
    user2.accept(user4);
    // user6.accept(user7);

    user3.accept(user5);

    user4.accept(user5);




    user6.accept(user1);
    user6.accept(user4);
    user7.accept(user2);
    user7.accept(user3);

    system("cls");

    while (app)
    {
        short choice = 0;


        while (true)
        {
            ConsoleUtils::setConsoleColor(8);
            cout << "---------Welcome---------\n";
            cout << "[1] Login\n[2] Signup\n";
            cout << "Enter your choice: ";

            cin >> choice;


            if (cin.fail() || (choice != 1 && choice != 2)) {
                ConsoleUtils::setConsoleColor(4);
                cout << "Invalid input! Please enter 1 or 2.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else {
                break;
            }
        }


        if (choice == 1)
        {
            u = test->login();
            if (u == nullptr) {
                ConsoleUtils::setConsoleColor(4);
                cout << "Cannot log in.\n";
            }
        }
        else if (choice == 2)
        {
            test->signup();
            u = test->login();
            if (u == nullptr) {
                ConsoleUtils::setConsoleColor(4);
                cout << "Cannot log in.\n";
            }
        }

        // Proceed if login/signup successful
        if (u != nullptr)
        {
            Graph::UserNode& user = *u;
            ConsoleUtils::setConsoleColor(3);
            cout << "Welcome, " << user.first_name << "!\n";

            // Example of modifying user data
           // user.first_name = "UpdatedName";
            //cout << "Updated name: " << user.first_name << "\n";

            // User options
            bool loggedIn = true;
            while (loggedIn)
            {
                ConsoleUtils::setConsoleColor(8);
                cout << "[1] View my profile\n[2] View my friends\n[3] Search\n[4] People you may know\n[5] Logout\n[6]Show requests \n[7]Exit \n";
                short option;

                cout << "Enter your choice: \n";
                cin >> option;

                // Check for valid input
                if (cin.fail()) {
                    ConsoleUtils::setConsoleColor(4);
                    cout << "Invalid input! Please enter a number.\n";
                    cin.clear(); // Clear the input stream
                    cin.ignore(1000, '\n'); // Discard invalid input
                    continue;
                }
                string usname;
                Vector<Graph::UserNode> v;
                switch (option)
                {
                case 1:
                    user.view_MY_profile();
                    break;
                case 2:
                    if (user.friends.empty())
                    {
                        ConsoleUtils::setConsoleColor(4);
                        cout << "List is empty!\n";

                    }
                    else
                    {
                        user.view_friends();
                        int n;
                        ConsoleUtils::setConsoleColor(8);
                        cout << "Enter index of friend<3 \n[-1] Back \n";
                        cin >> n;

                        if (n == -1)
                        {
                            break;
                        }
                        else
                        {

                            Graph::UserNode* anode = user.friends.search_by_index(n);

                            short x;
                            ConsoleUtils::setConsoleColor(8);
                            cout << "[1]View profile\n[2]Remove Friend\n[3]Classify Friend\n[4]Back \n";
                            cin >> x;
                            if (x == 1)
                            {
                                user.view_profile(*anode);
                                break;
                            }
                            else if (x == 2)
                            {

                                user.friends.remove(*anode);
                                anode->friends.remove(user);
                            }
                            else if (x == 3) {

                                user.friends.classify(anode->getUsername());
                                user.friends.sort();

                            }
                            else if (x == 4)
                            {
                                break;
                            }

                            else
                            {
                                ConsoleUtils::setConsoleColor(4);
                                cout << "Invalid\n";
                            }
                        }
                    }
                    break;
                case 3:
                    ConsoleUtils::setConsoleColor(8);
                    cout << "Enter name of the username: ";
                    cin >> usname;
                    user.searchByUsername(usname);
                    break;
                case 4:
                    user.people_you_may_know();


                    break;
                case 5:
                    ConsoleUtils::setConsoleColor(6);
                    cout << "Logging out...\n";
                    loggedIn = false;
                    break;
                case 6:
                    user.show_requests();
                    break;
                case 7:
                    return 0;
                    break;

                default:
                    ConsoleUtils::setConsoleColor(4);
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            }
        }

        // Clean up dynamically allocated memory

    }
    delete test;

}