#pragma once
#define NOMINMAX
#include "HashTable.h"
#include "linkedList.h"
#include "Vector.h"
#include "Pair.h"
#include <ctime>
#include <cstdlib>
#include "PriorityQueue.h"
#include "ConsoleUtils.h"
using namespace std;

class Graph
{
public:
	class UserNode {
		static int num_id;

	public:
		LinkedList<UserNode> requests;
		LinkedList<UserNode> friends;
		bool privacy;
		string address;
		string phone_number;
		string first_name;
		string last_name;
		string username;
		int index_of_hash;
		string password;


		// Constructors and Destructors
		UserNode(string first_name, string last_name, string nusername, string pass, bool privacy, string address, string phone_number);
		UserNode();
		UserNode(const UserNode& other);
		~UserNode();
		// Operators
		UserNode& operator=(const UserNode& other);
		bool operator<(const UserNode& other) const {
			return this->username < other.username;
		}
		bool operator>(const UserNode& other) const {
			return this->username > other.username;
		}
		friend std::ostream& operator<<(std::ostream& os, const UserNode& user);
		friend bool operator==(const UserNode& lhs, const UserNode& rhs);
		//Setters and Getters
		void set_name(string first, string last);
		void set_privacy(bool priv);
		void set_address(string address);
		void set_username(string name);
		void set_password(string pass);
		void set_phonenumber(string phone);
		string get_firstname() { return first_name; }
		string get_lastname() { return last_name; }
		string get_password() {
			return password;
		}
		string getUsername() { return this->username; }
		string get_phonenumber() { return phone_number; }
		string get_address() { return address; }
		bool get_privacy() { return privacy; }
		// Methods
		bool searchfriends(string username);
		bool searchrequests(string username);
		void send_request(UserNode& Sent_request_to);
		void accept(UserNode& Sender_of_request);
		void decline(UserNode& Sender_of_request);
		void show_requests();
		void view_profile(UserNode& to_view);
		void view_MY_profile();
		void view_myData();
		void view_myRealDATA();
		void view_friends();
		void modify_data();
		void searchByUsername(const string& username);
		UserNode* login();
		void signup();
		void people_you_may_know();
		Vector<UserNode> mutual_friends();
		void degree(Vector<UserNode>& v);
		void randomized(Vector<UserNode>& v);
	};

	static Vector<int> indexes;
	static HashTable <UserNode> hashex_login; // Database of users

};