#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
// declaration of attributes of graph class
int Graph::UserNode::num_id = 0;
HashTable<Graph::UserNode> Graph::hashex_login;
Vector<int> Graph::indexes;


// Constructors and Destructors

Graph::UserNode::UserNode(string first_name, string last_name, string nusername, string pass, bool privacy, string address, string phone_number) {
    this->first_name = first_name;
    this->last_name = last_name;
    this->username = nusername;
    this->password = pass;
    this->privacy = privacy;
    this->address = address;
    this->phone_number = phone_number;
    int sum_username = 0;
    for (int i = 0; i < username.size(); i++) {
        sum_username += username[i];
    }
    /*int sum_off_name = 0;
    sum_off_name = first_name[0] + first_name[1] + last_name[0] + last_name[1];*/
    int ind = hashex_login.hash(sum_username);
    hashex_login.insert(this, sum_username);
    if (!indexes.contains(ind)) {
        indexes.push_back(ind);
    }
    std::ofstream file("output.txt", std::ios::app); // Open in append mode
    if (file) {
        file << "User added to the system: " << username
            << " (First Name: " << first_name
            << ", Last Name: " << last_name << ")" << std::endl;
    }
    else {
        std::cerr << "Error: Could not open output.txt for logging." << std::endl;
    }
    file.close();

    //hashex_database.insert(this, sum_off_name);
}

Graph::UserNode::~UserNode() {
    //cout << "hii";
    requests.clear();
    friends.clear();

    // Output a message for debugging purposes (optional)
   // std::cout << "Destructor called for UserNode: " << username << std::endl;
}

Graph::UserNode::UserNode() : privacy(true) {}

Graph::UserNode::UserNode(const UserNode& other)
    : first_name(other.first_name), last_name(other.last_name), username(other.username), password(other.password),
    privacy(other.privacy), address(other.address), phone_number(other.phone_number),
    index_of_hash(other.index_of_hash) {
    // Deep copy of LinkedLists (assuming LinkedList has its own copy constructor)
    requests = other.requests;
    friends = other.friends;
}

//Operators

Graph::UserNode& Graph::UserNode:: operator=(const UserNode& other) {
    if (this != &other) {  // self-assignment check
        // Assign basic member variables
        first_name = other.first_name;
        last_name = other.last_name;
        username = other.username;
        password = other.password;
        privacy = other.privacy;
        address = other.address;
        phone_number = other.phone_number;
        index_of_hash = other.index_of_hash;

        // Deep copy of LinkedLists
        requests = other.requests;
        friends = other.friends;
    }
    return *this;  // return current object to allow assignment chaining
}

bool operator==(const Graph::UserNode& lhs, const Graph::UserNode& rhs) {

    return lhs.username == rhs.username;

}

ostream& operator<<(std::ostream& os, const Graph::UserNode& user) {
    ConsoleUtils::setConsoleColor(6);
    os << "Username: " << user.username;
    return os;
}



// Setters and getters

void Graph::UserNode::set_name(string first, string last) {
    first_name = first;
    last_name = last;
}

void Graph::UserNode::set_privacy(bool priv) {
    privacy = priv;
}

void Graph::UserNode::set_address(string address) {
    this->address = address;
}

void Graph::UserNode::set_username(string name) {
    username = name;
}

void Graph::UserNode::set_password(string pass) {
    password = pass;
}

void Graph::UserNode::set_phonenumber(string phone) {
    phone_number = phone;
}

//Methods

bool Graph::UserNode::searchfriends(string username)
{
    LinkedList<UserNode>::accessnode* ptr = this->friends.head;
    while (ptr != nullptr) {
        if (ptr->OG_NODE->getUsername() == username) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool Graph::UserNode::searchrequests(string username)
{
    LinkedList<UserNode>::accessnode* ptr = this->requests.head;
    while (ptr != nullptr) {
        if (ptr->OG_NODE->getUsername() == username) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void Graph::UserNode::send_request(UserNode& newnode) {
    ConsoleUtils::setConsoleColor(2);
    cout << "Request sent to: " << newnode.getUsername() << endl;
    newnode.requests.append(this);

    // Write to the file
    std::ofstream file("output.txt", std::ios::app); // Open the file in append mode
    if (file.is_open()) {
        file << "Request sent from " << this->getUsername() << " to " << newnode.getUsername() << ".\n";
        file.close(); // Close the file after writing
    }
    else {
        cerr << "Unable to open the file for logging.\n";
    }
}

void Graph::UserNode::accept(UserNode& Sender_of_request) {
    std::ofstream file("output.txt", std::ios::app);

    if (!file) {
        std::cerr << "Error opening file for logging." << std::endl;
        return;
    }

    UserNode* f = &Sender_of_request;


    friends.append(f);
    Sender_of_request.friends.append(this);


    requests.remove(Sender_of_request);


    file << this->getUsername() << " added " << Sender_of_request.getUsername()
        << " to their friends list.\n";

    ConsoleUtils::setConsoleColor(2);
    cout << "Request accepted.\n";


    file.close();
}

void Graph::UserNode::decline(UserNode& Sender_of_request) {
    std::ofstream file("output.txt", std::ios::app); // Open the file in append mode

    if (!file) {
        std::cerr << "Error opening file for logging." << std::endl;
        return;
    }
    requests.remove(Sender_of_request);
    file << this->getUsername() << " declined a friend request from " << Sender_of_request.getUsername() << ".\n";
    ConsoleUtils::setConsoleColor(2);
    cout << Sender_of_request.getUsername() << " has been declined successfully! ";
    file.close();
}

void Graph::UserNode::show_requests() {
    requests.IterateByIndex();
    int n;
    if (requests.empty()) {
        ConsoleUtils::setConsoleColor(2);
        cout << "List is empty!\n";
        return;
    }
    ConsoleUtils::setConsoleColor(8);
    cout << "\nEnter index of your choice<3\n[-1] Back \n";

    while (true) {
        cin >> n;

        if (cin.fail() || n <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }


        if (n == -1) {
            return;
        }
        if (n >= 1 && n <= requests.size()) {
            break;
        }
        else {
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid index" << endl;
        }
    }

    UserNode& userrr = *(requests.search_by_index(n));

    short x = 0;
    while (x != 4) {
        ConsoleUtils::setConsoleColor(8);
        cout << "[1] Accept\n[2] Decline\n[3] View Profile\n[4] Back\n";
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }


        if (x == 1) {
            this->accept(userrr);
            break;
        }
        else if (x == 2) {
            this->decline(userrr);
            break;
        }
        else if (x == 3) {
            this->view_profile(userrr);
            break;
        }
        else if (x == 4) {
            return;
        }
        else {
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Graph::UserNode::view_profile(UserNode& to_view) {

    bool k = 1;
    UserNode* point = &to_view;
    while (k == 1)
    {
        ConsoleUtils::setConsoleColor(6);
        cout << "Profile Of " << point->getUsername() << endl;
        cout << "------------" << endl;

        if (point->get_privacy() == 1)
        {
            if (!(this->searchfriends(point->getUsername())))
            {
                ConsoleUtils::setConsoleColor(4);
                std::cout << "Sorry,This account is private\n";
                k = 0;
                return;
            }
        }

        (*(point)).view_myData();
        ConsoleUtils::setConsoleColor(8);
        std::cout << "[1]View friends\n[2]back\n";
        short a;
        std::cin >> a;
        if (a == 1)
        {

            (*(point)).view_friends();
            int n;
            ConsoleUtils::setConsoleColor(8);
            std::cout << "Enter index < 3 \n[-1] Back to main\n";
            std::cin >> n;
            if (n == -1)
            {
                return;
            }
            else
            {
                UserNode* anode = (*(point)).friends.search_by_index(n);
                UserNode* userp = point;
                ConsoleUtils::setConsoleColor(6);
                cout << "Checking if username is in friends list..." << endl;
                bool friendd = this->searchfriends(anode->getUsername());
                if (friendd)
                {
                    ConsoleUtils::setConsoleColor(8);
                    cout << "[1]View Profile\n[2]Remove Friend \n [3]Back\n";
                    short x;
                    std::cin >> x;
                    if (x == 1)
                    {
                        ConsoleUtils::setConsoleColor(6);
                        std::cout << "user name: " << endl;
                        std::cout << anode->getUsername() << endl;
                        view_profile(*anode);
                    }
                    else if (x == 2)
                    {
                        this->friends.remove(*anode);
                        anode->friends.remove(*this);
                        ConsoleUtils::setConsoleColor(2);
                        std::cout << anode->getUsername() << " Removed Successfully!" << endl;
                    }
                    else if (x == 3)
                    {

                        return;
                    }
                    else {
                        ConsoleUtils::setConsoleColor(4);
                        std::cout << "Invalid Input" << endl;
                        break;
                    }
                }
                else if (this->searchrequests(anode->getUsername()))
                {
                    ConsoleUtils::setConsoleColor(8);
                    std::cout << "[1]View Profile\n[2]Accept \n [3] Decline\n [4] Back\n";
                    short x;
                    std::cin >> x;
                    if (x == 1) {
                        ConsoleUtils::setConsoleColor(6);
                        std::cout << "user name: " << endl;
                        std::cout << anode->getUsername() << endl;
                        anode->view_myData();
                    }
                    else if (x == 2) {
                        this->accept(*anode);
                        ConsoleUtils::setConsoleColor(2);
                        std::cout << "ACCEPTED" << endl;
                    }
                    else if (x == 3) {

                        this->decline(*anode);
                        ConsoleUtils::setConsoleColor(2);
                        std::cout << "DECLINED" << endl;

                    }
                    else if (x == 4) {

                        break;
                    }
                    else {
                        ConsoleUtils::setConsoleColor(4);
                        std::cout << "Invalid Input" << endl;
                    }

                }
                else if (anode->searchrequests(this->username)) {
                    ConsoleUtils::setConsoleColor(8);
                    std::cout << "[1]View Profile\n[2] Remove Request \n [3]Back \n";
                    short x;
                    std::cin >> x;
                    if (x == 1) {
                        ConsoleUtils::setConsoleColor(6);
                        std::cout << "user name: " << endl;
                        std::cout << anode->getUsername() << endl;
                        anode->view_myData();

                    }
                    else if (x == 2) {
                        anode->requests.remove(*this);
                        ConsoleUtils::setConsoleColor(2);
                        std::cout << "REQUEST REMOVED \n";

                    }
                    else if (x == 3) {

                        break;
                    }
                    else {
                        ConsoleUtils::setConsoleColor(4);
                        std::cout << "Invalid Input" << endl;
                    }

                }
                else if (this->username == anode->getUsername()) {
                    this->view_MY_profile();
                }
                else
                {
                    int x = 0;

                    while (true)
                    {
                        ConsoleUtils::setConsoleColor(8);
                        std::cout << "[1]View Profile \n[2]Add Friend \n[3] Back\n";
                        short x;
                        std::cin >> x;
                        if (x == 1)

                        {
                            ConsoleUtils::setConsoleColor(6);
                            std::cout << "user name: " << endl;
                            std::cout << anode->getUsername();
                            view_profile(*anode);
                            break;


                        }
                        else if (x == 2)
                        {
                            this->send_request(*anode);
                            ConsoleUtils::setConsoleColor(2);
                            std::cout << "Added successfully!" << endl;
                            break;
                        }
                        else if (x == 3)
                        {

                            break;
                        }
                    }
                }
            }
        }
        else if (a == 2)
        {
            return;
        }
        else
        {
            ConsoleUtils::setConsoleColor(4);
            std::cout << "Invalid" << endl;
            return;
        }






    }
    cout << "----------------------------------------" << endl;


}

void Graph::UserNode::view_MY_profile() {

    bool c = 1;
    while (c == 1) {
        ConsoleUtils::setConsoleColor(8);
        cout << "--------------------------------------" << endl;
        this->view_myRealDATA();
        cout << "\n[1]Modify Data\n[2]Back \n";
        short choice;
        cin >> choice;
        if (choice == 1)
            this->modify_data();
        else if (choice == 2) {
            return;

        }
        else {
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid\n";
            break;
        }
        ConsoleUtils::setConsoleColor(8);
        cout << "--------------------------------------" << endl;
    }
}

void Graph::UserNode::view_myData() {
    ConsoleUtils::setConsoleColor(6);
    cout << "First name: " << this->get_firstname() << endl << "Last name:  " << this->get_lastname() << endl;
    cout << "Username: " << this->getUsername() << endl;

    cout << "Phone number: " << this->get_phonenumber() << "\nAddress: " << this->get_address() << endl;

}

void Graph::UserNode::view_myRealDATA() {
    ConsoleUtils::setConsoleColor(6);
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "First name: " << this->get_firstname() << endl << "Last name:  " << this->get_lastname() << endl;
    cout << "Username: " << this->getUsername() << endl;
    cout << "Phone number: " << this->get_phonenumber() << "\nAddress: " << this->get_address() << endl;
    cout << "PassWord: " << this->password;
}

void Graph::UserNode::view_friends() {
    friends.IterateByIndex();

    cout << endl;
}

void Graph::UserNode::modify_data() {
    ConsoleUtils::setConsoleColor(8);
    cout << "What data do you want to modify?\n";
    cout << "[1] Password\n[2]Address\n[3]Phone Number\n[4]Return Home\n";
    short option;
    string password;
    string address;
    string phonenumber;
    bool isValid = false;
    cin >> option;
    switch (option)
    {
    case 1:
        ConsoleUtils::setConsoleColor(3);
        cout << "Enter new password: ";
        cin >> password;
        this->set_password(password);
        ConsoleUtils::setConsoleColor(2);
        cout << "password updated succeessfully!";
        break;
    case 2:
        ConsoleUtils::setConsoleColor(3);
        cout << "Enter new Address: ";
        cin >> address;
        this->set_address(address);
        ConsoleUtils::setConsoleColor(2);
        cout << "address updated succeessfully!";
        break;
    case 3:


        while (!isValid) {
            ConsoleUtils::setConsoleColor(3);
            cout << "Enter your phone number: \n";
            cin >> phonenumber;
            if (phonenumber.length() != 11) {
                ConsoleUtils::setConsoleColor(4);
                cout << "Invalid phone number. It must be 11 digits long.\n";
                continue;
            }

            string prefix = phonenumber.substr(0, 3);
            if (prefix != "010" && prefix != "011" && prefix != "012" && prefix != "015") {
                ConsoleUtils::setConsoleColor(4);
                cout << "Invalid phone number. It must start with 010, 011, 012, or 015.\n";
                continue;
            }

            bool allDigits = true;
            for (char c : phonenumber) {
                if (!isdigit(c)) {
                    allDigits = false;
                    break;
                }
            }

            if (!allDigits) {
                ConsoleUtils::setConsoleColor(4);
                cout << "Invalid phone number. It must contain only digits.\n";
                continue;
            }

            isValid = true;
        }
        this->set_phonenumber(phonenumber);
        ConsoleUtils::setConsoleColor(2);
        cout << "phone number updated succeessfully!";
        break;

    case 4:
        ConsoleUtils::setConsoleColor(6);
        cout << "returning home...";
        return;

    default:
        ConsoleUtils::setConsoleColor(4);
        cout << "Invalid";
        break;
    }
    ConsoleUtils::setConsoleColor(3);
    cout << "---------------------------------------------------------------" << endl;

}

void Graph::UserNode::searchByUsername(const std::string& username) {

    std::fstream file("output.txt", std::ios::out | std::ios::app);


    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }


    int sum_username = 0;
    for (char c : username) {
        sum_username += c;
    }

    file << "Sum of username characters: " + std::to_string(sum_username) << std::endl;


    int index = hashex_login.hash(sum_username);

    file << "Calculated hash index: " + std::to_string(index) << std::endl;

    LinkedList<UserNode>::accessnode* temp = hashex_login.buckets[index].head;
    UserNode* temp1 = nullptr;

    try {

        file << "Calling HASHget..." << std::endl;
        file << "Searching at index: " + std::to_string(index) << std::endl;

        while (temp != nullptr) {

            file << "Checking username: " + temp->OG_NODE->getUsername() +
                ", password: " + temp->OG_NODE->get_password() << std::endl;
            if (temp->OG_NODE->getUsername() == username) {
                temp1 = temp->OG_NODE;
                break;
            }
            temp = temp->next;
        }
    }
    catch (const std::runtime_error& e) {

        file << "Error: " + std::string(e.what()) << std::endl;
        return;
    }

    if (temp1 != nullptr) {
        bool v = true;
        while (v) {
            file << "Successfully retrieved targetNode" << std::endl;
            UserNode& ref = *temp1;


            file << "Checking if username is in friends list..." << std::endl;
            bool friendd = this->searchfriends(username);
            if (friendd) {
                ConsoleUtils::setConsoleColor(8);
                cout << "[1]View Profile\n[2]Remove Friend\n[3]Back\n";
                short x;
                std::cin >> x;
                if (x == 1) {
                    ConsoleUtils::setConsoleColor(6);
                    cout << "user name: " << std::endl;
                    cout << temp1->getUsername();
                    view_profile(ref);
                    break;
                }
                else if (x == 2) {
                    this->friends.remove(*temp1);
                    temp1->friends.remove(*this);
                    ConsoleUtils::setConsoleColor(2);
                    file << temp1->getUsername() + " Removed Successfully!" << std::endl;
                }
                else if (x == 3) {
                    v = false;
                    break;
                }
                else {
                    ConsoleUtils::setConsoleColor(4);
                    cout << "Invalid Input" << std::endl;
                }
            }
            else if (this->searchrequests(username)) {
                ConsoleUtils::setConsoleColor(8);
                cout << "[1]View Profile\n[2]Accept\n[3]Decline\n[4]Back\n";
                short x;
                cin >> x;
                if (x == 1) {
                    ConsoleUtils::setConsoleColor(6);
                    cout << "user name: " << std::endl;
                    cout << temp1->getUsername();
                    view_profile(*temp1);
                }
                else if (x == 2) {
                    this->accept(ref);
                    file << "ACCEPTED" << std::endl;
                }
                else if (x == 3) {
                    this->decline(ref);
                    file << "DECLINED" << std::endl;
                }
                else if (x == 4) {
                    v = false;
                    break;
                }
                else {
                    ConsoleUtils::setConsoleColor(4);
                    cout << "Invalid Input" << std::endl;
                }
            }
            else if (ref.searchrequests(this->username)) {
                ConsoleUtils::setConsoleColor(8);
                std::cout << "[1]View Profile\n[2]Remove Request\n[3]Back\n";
                short x;
                std::cin >> x;
                if (x == 1) {
                    ConsoleUtils::setConsoleColor(6);
                    std::cout << "user name: " << std::endl;
                    std::cout << temp1->getUsername();
                    view_profile(ref);
                }
                else if (x == 2) {
                    ref.requests.remove(*this);
                    ConsoleUtils::setConsoleColor(2);
                    file << "REQUEST REMOVED" << std::endl;
                }
                else if (x == 3) {
                    v = false;
                    break;
                }
                else {
                    ConsoleUtils::setConsoleColor(4);
                    std::cout << "Invalid Input" << std::endl;
                }
            }
            else if (this->getUsername() == temp1->username) {
                this->view_MY_profile();
                break;
            }
            else {
                while (true) {
                    ConsoleUtils::setConsoleColor(8);
                    std::cout << "[1]View Profile\n[2]Add Friend\n[3]Back\n";
                    short x;
                    std::cin >> x;
                    if (x == 1) {
                        view_profile(ref);
                    }
                    else if (x == 2) {
                        send_request(*temp1);
                        ConsoleUtils::setConsoleColor(2);
                        file << "Added successfully!" << std::endl;
                        break;
                    }
                    else if (x == 3) {
                        v = false;
                        break;
                    }
                    else {
                        ConsoleUtils::setConsoleColor(4);
                        std::cout << "Invalid Input" << std::endl;
                    }
                }
            }
        }
    }
    else {
        ConsoleUtils::setConsoleColor(4);
        file << "Invalid username" << std::endl;
        std::cout << "Invalid username" << std::endl;
        return;
    }
    ConsoleUtils::setConsoleColor(10);
    // Log the end of the operation
    file << "------------------------------------------------------------" << std::endl;
    cout << "--------------------------------------------------------------" << endl;

    // Close the file after writing
    file.close();
}

Graph::UserNode* Graph::UserNode::login() {
    std::ofstream file("output.txt", std::ios::app); // Open the file in append mode

    if (!file) {
        std::cerr << "Error opening file for logging." << std::endl;
        return nullptr;
    }

    string username;
    string password;

    while (true) {
        ConsoleUtils::setConsoleColor(8);
        std::cout << "Enter your username: \n";
        std::cin >> username;
        std::cout << "Enter your password: \n";
        std::cin >> password;

        int sum = 0;
        for (char c : username) {
            sum += c;
        }

        int index = hashex_login.hash(sum);



        file << "Searching at index: " << index << std::endl;

        LinkedList<UserNode>::accessnode* temp = hashex_login.buckets[index].head;

        while (temp != nullptr) {
            // Output username and password being checked to both console and file

            file << "Checking username: " << temp->OG_NODE->getUsername()
                << ", password: " << temp->OG_NODE->get_password() << std::endl;

            if (temp->OG_NODE->getUsername() == username && temp->OG_NODE->get_password() == password) {
                file.close(); // Close the file before returning
                return temp->OG_NODE;
            }
            temp = temp->next;
        }
        ConsoleUtils::setConsoleColor(4);
        std::cout << "Invalid username or password. Try again.\n";
        file << "Invalid username or password attempted: " << username << "\n";

        bool flag = true;

        while (flag) {
            ConsoleUtils::setConsoleColor(8);
            std::cout << "Do you want to sign up?\n[1] Yes\n[2] No\n";
            short x;

            // Input validation
            std::cin >> x;
            if (std::cin.fail()) {
                ConsoleUtils::setConsoleColor(4);
                std::cout << "Invalid input! Please enter 1 or 2.\n";
                std::cin.clear();           // Clear the input stream
                std::cin.ignore(1000, '\n'); // Discard invalid input
                continue;                    // Retry
            }

            if (x == 1) {
                signup();     // Call the signup function
                flag = false; // Exit the loop after signing up
            }
            else if (x == 2) {
                ConsoleUtils::setConsoleColor(4);
                std::cout << "Login again.\n";
                flag = false; // Exit the loop, returning to login prompt
            }
            else {
                ConsoleUtils::setConsoleColor(4);
                std::cout << "Invalid choice! Please enter 1 or 2.\n";
            }
        }
    }

    file.close(); // Close the file after exiting the loop
    return nullptr;
}

void Graph::UserNode::signup() {

    string fname;
    string lname;
    string nusername;
    string password;
    string phoneNumber;
    string address;
    bool priv;

    ConsoleUtils::setConsoleColor(8);
    cout << "Enter your first name: \n";
    cin >> fname;
    cout << "Enter your last name: \n";
    cin >> lname;

    bool flag = true;
    while (flag) {
        cout << "Enter your username: \n";
        cin >> nusername;

        int sum = 0;
        for (char c : nusername) {
            sum += c;
        }

        int index = hashex_login.hash(sum);
        LinkedList<UserNode>::accessnode* temp = hashex_login.buckets[index].head;
        flag = false;
        while (temp != nullptr) {
            if (nusername == temp->OG_NODE->getUsername()) {
                ConsoleUtils::setConsoleColor(4);
                cout << "This username is already taken. Please try another.\n";
                flag = true;
                break;
            }
            temp = temp->next;
        }
    }
    ConsoleUtils::setConsoleColor(8);
    cout << "Enter your password: \n";
    cin >> password;

    bool isValid = false;

    while (!isValid) {
        ConsoleUtils::setConsoleColor(8);
        cout << "Enter your phone number: \n";
        cin >> phoneNumber;
        if (phoneNumber.length() != 11) {
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid phone number. It must be 11 digits long.\n";
            continue;
        }

        string prefix = phoneNumber.substr(0, 3);
        if (prefix != "010" && prefix != "011" && prefix != "012" && prefix != "015") {
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid phone number. It must start with 010, 011, 012, or 015.\n";
            continue;
        }

        bool allDigits = true;
        for (char c : phoneNumber) {
            if (!isdigit(c)) {
                allDigits = false;
                break;
            }
        }

        if (!allDigits) {
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid phone number. It must contain only digits.\n";
            continue;
        }

        isValid = true;
    }
    ConsoleUtils::setConsoleColor(8);
    cout << "Enter your address: \n";
    cin >> address;

    while (true) {
        ConsoleUtils::setConsoleColor(6);
        cout << "Do you want your account to be private?\n[1] Yes\n[2] No\n";
        short x;
        cin >> x;
        if (x == 1) {
            priv = true;
            break;
        }
        else if (x == 2) {
            priv = false;
            break;
        }
        else {
            ConsoleUtils::setConsoleColor(4);
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }

    UserNode* user = new UserNode(fname, lname, nusername, password, priv, address, phoneNumber);

}

void Graph::UserNode::people_you_may_know() {

    Vector<UserNode> mutual = mutual_friends();
    degree(mutual);
    randomized(mutual);
    bool v = true;

    while (v) {
        ConsoleUtils::setConsoleColor(6);
        cout << "Suggestions" << endl;

        for (int i = 0; i < mutual.getSize(); i++) {
            cout << "[" << i + 1 << "] " << mutual[i] << endl;
        }
        ConsoleUtils::setConsoleColor(3);
        cout << "Choose the User you want \n [-1] back \n";

        int y;
        cin >> y;


        if (cin.fail() || y == 0 || y<-1 || y > mutual.getSize()) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (y != -1) {
                ConsoleUtils::setConsoleColor(4);
                cout << "Invalid choice! Please enter a number between 1 and " << mutual.getSize() << " or -1 to go back.\n";
            }
        }
        else if (y == -1) {
            ConsoleUtils::setConsoleColor(10);
            cout << "EXITING" << endl;
            v = 0;
            break;

        }
        else {
            searchByUsername(mutual[y - 1].getUsername());
        }
    }
    cout << endl;


}

Vector<Graph::UserNode> Graph::UserNode::mutual_friends()
{
    std::ofstream file("output.txt", std::ios::app); // Open the file in append mode
    if (!file) {
        std::cerr << "Error opening file for logging." << std::endl;
    }

    Vector<Pair<UserNode, int>> pair_vector;
    Vector<UserNode> visited;
    LinkedList<UserNode>::accessnode* temp1 = friends.head;
    LinkedList<UserNode>::accessnode* temp2;
    Pair< UserNode, int > pairNode;
    while (temp1 != nullptr) {
        temp2 = temp1->OG_NODE->friends.head;
        while (temp2 != nullptr) {
            if (temp2->OG_NODE != this && !(temp2->OG_NODE->searchfriends(this->getUsername())) && !(temp2->OG_NODE->searchrequests(this->getUsername())) && !(this->searchrequests(temp2->OG_NODE->getUsername()))) {
                if (!visited.contains(*(temp2->OG_NODE))) {
                    visited.push_back(*(temp2->OG_NODE));
                    pairNode.setFirst(*(temp2->OG_NODE));
                    pairNode.setSecond(1);
                    pair_vector.push_back(pairNode);
                }
                else {
                    for (int i = 0; i < pair_vector.getSize(); i++) {
                        if (pair_vector[i].getFirst().getUsername() == temp2->OG_NODE->getUsername()) {
                            pair_vector[i].setSecond(pair_vector[i].getSecond() + 1);
                            break;
                        }
                    }

                }

            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    PriorityQueue<Pair<UserNode, int>> priority;
    Vector <UserNode> to_be_returned;
    for (int i = 0; i < pair_vector.getSize(); i++) {
        priority.push(pair_vector[i]);
    }
    pair_vector.clear();
    while (!priority.empty()) {
        to_be_returned.push_back(priority.top().getFirst());
        if (file) {
            file << "Username: " << priority.top().getFirst().getUsername()
                << ", Mutual Count: " << priority.top().getSecond() << std::endl;
        }
        priority.pop();
    }
    file.close();
    
    return to_be_returned;
}

void Graph::UserNode::degree(Vector<UserNode>& visited)
{

    LinkedList<UserNode>::accessnode* temp1 = friends.head;
    LinkedList<UserNode>::accessnode* temp2;
    LinkedList<UserNode>::accessnode* temp3;
    while (temp1 != nullptr) {
        temp2 = temp1->OG_NODE->friends.head;

        while (temp2 != nullptr) {
            temp3 = temp2->OG_NODE->friends.head;

            while (temp3 != nullptr) {
                if (temp3->OG_NODE != this && !(temp3->OG_NODE->searchfriends(this->getUsername())) && !(temp3->OG_NODE->searchrequests(this->getUsername())) && !(this->searchrequests(temp3->OG_NODE->getUsername())) && !visited.contains(*(temp3->OG_NODE))) {
                    visited.push_back(*(temp3->OG_NODE));
                }
                temp3 = temp3->next;
            }
            temp2 = temp2->next;


        }
        temp1 = temp1->next;
    }


}

void Graph::UserNode::randomized(Vector<UserNode>& visited)
{

    int q = indexes.getSize();

    int i = 5;
    while (i && q) {
        srand(static_cast<unsigned int>(time(nullptr)));
        int randomNumber = rand() % q;
        LinkedList<UserNode>::accessnode* temp = hashex_login.buckets[indexes[randomNumber]].head;

        if (temp->OG_NODE != this && !(temp->OG_NODE->searchfriends(this->getUsername())) && !(temp->OG_NODE->searchrequests(this->getUsername())) && !(this->searchrequests(temp->OG_NODE->getUsername())) && !visited.contains(*(temp->OG_NODE)) && temp->OG_NODE != nullptr) {
            visited.push_back(*(temp->OG_NODE));
            i--;
        }
        q--;
    }

}