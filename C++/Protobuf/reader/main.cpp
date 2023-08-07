#include <iostream>
#include <string>
#include <fstream>

#include "../proto/addressbook.pb.h"

namespace {
    void ListPeople(const tutorial::AddressBook& address_book) {
        for (int person_index = 0; person_index < address_book.people_size(); ++person_index) {
            const tutorial::Person& person = address_book.people(person_index);

            std::cout << "Person ID: " << person.id() << std::endl;
            std::cout << "Name: " << person.name() << std::endl;
            if (person.has_email()) {
                std::cout << "E-mail address: " << person.email() << std::endl;
            }

            for (int phone_index = 0; phone_index < person.phones_size(); ++phone_index) {
                const tutorial::Person::PhoneNumber& phone_number = person.phones(phone_index);

                switch (phone_number.type())
                {
                case tutorial::Person::MOBILE:
                    std::cout << "Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    std::cout << "Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    std::cout << "Work phone #: ";
                    break;
                default:
                    break;
                }

                std::cout << phone_number.number() << std::endl;
            }

        }
    }
}

int main(int argc, char** argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << std::endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
        std::fstream input(argv[1], std::ios::in | std::ios::binary);
        if (!address_book.ParseFromIstream(&input)) {
            std::cerr << "Failed to parse address book." << std::endl;
            return -1;
        }
    }

    ListPeople(address_book);

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}