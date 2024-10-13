#ifndef FIRM_SYS_HPP
#define FIRM_SYS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <list>
#include "firm.hpp"
#include "linked_list_template.hpp"
#include "vector_template.hpp"

class IFirmSystem {
public:
    virtual void addFirm(const std::string& firmID, const std::string& firmName) = 0;
    virtual void removeFirm(const std::string& firmID) = 0;
    virtual std::shared_ptr<IFirm> getFirm(const std::string& firmID) const = 0;
    // virtual std::string cleanString(const std::string& input) = 0;
    virtual void loadFirms(const std::string& filename) = 0;
    virtual void loadPatentsFromCSV(const std::string& filename) = 0;
    virtual void addPatentFirm(const std::string& firmID, Patent& patent) = 0;
    virtual void removePatentFirm(const std::string& firmID, const std::string& patentID) = 0;
    virtual void transferPatent(const std::string& fromFirmID, const std::string& toFirmID, const std::string& patentID) = 0;
    virtual void displayFirm(const std::string& firmID) const = 0;
    virtual void displayFirms() const = 0;
    virtual void displayFirmsID() const = 0;
    virtual ~IFirmSystem() {}
    // 可以加查找；按id；按title-关键词、tf-idf
};

class BaseFirmSystem : public IFirmSystem {
public:

    std::string cleanString(const std::string& input) {
        std::string cleaned = input;

        cleaned.erase(cleaned.begin(), std::find_if(cleaned.begin(), cleaned.end(), [](unsigned char c) {
            return !std::isspace(c);
        }));

        cleaned.erase(std::find_if(cleaned.rbegin(), cleaned.rend(), [](unsigned char c) {
            return !std::isspace(c);
        }).base(), cleaned.end());

        return cleaned;
    }
 
    void loadFirms(const std::string& filename) override {
        
        std::ifstream file(filename);
        std::string line, firmID, firmName;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open FirmData.csv" << std::endl;
            file.close();
        }

        getline(file, line);
        
        while (getline(file, line)) {
            std::stringstream ss(line);
            getline(ss, firmID, ',');
            getline(ss, firmName, ',');

            firmName = cleanString(firmName);
            firmID = cleanString(firmID);

            addFirm(firmID, firmName);
        }

        file.close();
    }
    
    void loadPatentsFromCSV(const std::string& filename) override {
        std::ifstream file(filename);
        std::string line, patentID, grantdate, appldate, patent_title, country, firmID;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open PatentData.csv" << std::endl;
            file.close();
        }

        getline(file, line);
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::getline(ss, patentID, ',');
            std::getline(ss, grantdate, ',');
            std::getline(ss, appldate, ',');

            if (line.find('"') != std::string::npos) {
                getline(ss, patent_title, '"');
                getline(ss, patent_title, '"');
                ss.ignore();
            } else {
                getline(ss, patent_title, ',');
            }

            getline(ss, country, ',');
            getline(ss, firmID, ',');

            firmID = cleanString(firmID);
            Patent p(patentID, grantdate, appldate, patent_title, country, firmID);
            addPatentFirm(firmID, p);
        }

        file.close();
    }

    void displayFirm(const std::string& firmID) const override {
        auto firm = getFirm(firmID);
        if (firm) {
            std::cout << "Firm ID: " << firm->getFirmID() << ", Firm Name: " << firm->getFirmName() << std::endl;
            std::cout << "Number of Patents: " << firm->getPatentCount() << std::endl;
            firm->displayPatents();
            std::cout << "-----------------------------------" << std::endl;
        }
    }

};

class FirmSystemVector : public BaseFirmSystem {
private:
    myVector<std::shared_ptr<IFirm>> fs;
    FirmType firmType;
public:
    FirmSystemVector(FirmType type) : firmType(type) {}

    void addFirm(const std::string& firmID, const std::string& firmName) override {
        std::shared_ptr<IFirm> firm;
        switch (firmType) {
            case FirmType::LinkedList:
                firm = std::make_shared<FirmLinkedList>(firmID, firmName);
                break;
            case FirmType::Vector:
                firm = std::make_shared<FirmVector>(firmID, firmName);
                break;
            case FirmType::UnorderedMap:
                firm = std::make_shared<FirmUnorderedMap>(firmID, firmName);
                break;
        }
        fs.push_back(firm);
    }

    void removeFirm(const std::string& firmID) override {
        auto it = std::find_if(fs.begin(), fs.end(), [&](const std::shared_ptr<IFirm>& f) {
            return f->getFirmID() == firmID;
        });
        if (it != fs.end()) {
            fs.remove_at(it - fs.begin());
            std::cout << "Firm removed successfully." << std::endl;
        } else {
            std::cerr << "Firm not found." << std::endl;
        }
    }

    void addPatentFirm(const std::string& firmID, Patent& patent) override {
        auto it = std::find_if(fs.begin(), fs.end(), [&](const std::shared_ptr<IFirm>& f) {
            return f->getFirmID() == firmID;
        });
        if (it != fs.end()) {
            (*it)->addPatent(patent);
        } else {
            std::cerr << "Firm not found." << std::endl;
        }
    }

    void removePatentFirm(const std::string& firmID, const std::string& patentID) override {
        auto it = std::find_if(fs.begin(), fs.end(), [&](const std::shared_ptr<IFirm>& f) {
            return f->getFirmID() == firmID;
        });
        if (it != fs.end()) {
            (*it)->removePatent(patentID);
        }
    }

    void transferPatent(const std::string& fromFirmID, const std::string& toFirmID, const std::string& patentID) override {
        std::shared_ptr<IFirm> fromFirm = nullptr;
        std::shared_ptr<IFirm> toFirm = nullptr;

        for (auto& f : fs) {
            if (f->getFirmID() == fromFirmID) {
                fromFirm = f;
            } else if (f->getFirmID() == toFirmID) {
                toFirm = f;
            }
        }

        if (fromFirm && toFirm) {
            Patent p = fromFirm->getPatent(patentID);
            toFirm->addPatent(p);
            fromFirm->removePatent(patentID);
        } else {
            std::cerr << "Error: One or both firms not found." << std::endl;
        }
    }

    std::shared_ptr<IFirm> getFirm(const std::string& firmID) const override {
        auto it = std::find_if(fs.begin(), fs.end(), [&](const std::shared_ptr<IFirm>& f) {
            return f->getFirmID() == firmID;
        });
        if (it != fs.end()) {
            return *it;
        }
        std::cerr << "Firm not found." << std::endl;
        return nullptr;
    }

    void displayFirmsID() const override {
        if (fs.size() == 0) {
            std::cout << "No firms available." << std::endl;
            return;
        }

        for (const auto& firm : fs) {
            std::cout << firm->getFirmName() << "  ";
            std::cout << firm->getFirmID() << "\n";
        }
        std::cout << std::endl;
    }

    void displayFirms() const override {
        if (fs.size() == 0) {
            std::cout << "No firms available." << std::endl;
            return;
        }

        for (const auto& firm : fs) {
            displayFirm(firm->getFirmID());
        }
    }
};

class FirmSystemUnorderedMap : public BaseFirmSystem {
private:
    std::unordered_map<std::string, std::shared_ptr<IFirm>> fs;
    FirmType firmType;
public:
    FirmSystemUnorderedMap(FirmType type) : firmType(type) {}

    void addFirm(const std::string& firmID, const std::string& firmName) override {
        std::shared_ptr<IFirm> firm;
        switch (firmType) {
            case FirmType::LinkedList:
                firm = std::make_shared<FirmLinkedList>(firmID, firmName);
                break;
            case FirmType::Vector:
                firm = std::make_shared<FirmVector>(firmID, firmName);
                break;
            case FirmType::UnorderedMap:
                firm = std::make_shared<FirmUnorderedMap>(firmID, firmName);
                break;
        }
        fs[firmID] = firm;
    }

    void removeFirm(const std::string& firmID) override {
        auto it = fs.find(firmID);
        if (it != fs.end()) {
            fs.erase(it);
            std::cout << "Firm removed successfully." << std::endl;
        } else {
            std::cerr << "Firm not found." << std::endl;
        }
    }

    void addPatentFirm(const std::string& firmID, Patent& patent) override {
        auto it = fs.find(firmID);
        if (it != fs.end()) {
            it->second->addPatent(patent);
        } else {
            std::cerr << "Firm not found." << std::endl;
        }
    }

    void removePatentFirm(const std::string& firmID, const std::string& patentID) override {
        auto it = fs.find(firmID);
        if (it != fs.end()) {
            it->second->removePatent(patentID);
        } else {
            std::cerr << "Firm not found." << std::endl;
        }
    }

    void transferPatent(const std::string& fromFirmID, const std::string& toFirmID, const std::string& patentID) override {
        auto fromIt = fs.find(fromFirmID);
        auto toIt = fs.find(toFirmID);

        if (fromIt != fs.end() && toIt != fs.end()) {
            Patent p = fromIt->second->getPatent(patentID);
            toIt->second->addPatent(p);
            fromIt->second->removePatent(patentID);
        } else {
            std::cerr << "Error: One or both firms not found." << std::endl;
        }
    }

    std::shared_ptr<IFirm> getFirm(const std::string& firmID) const override {
        auto it = fs.find(firmID);
        if (it != fs.end()) {
            return it->second;
        }
        std::cerr << "Firm not found." << std::endl;
        return nullptr;
    }

    void displayFirmsID() const override {
        if (fs.empty() == 0) {
            std::cout << "No firms available." << std::endl;
            return;
        }

        for (const auto& pair : fs) {
            std::cout << pair.second->getFirmName() << "  ";
        }
        std::cout << std::endl;
        for (const auto& pair : fs) {
            std::cout << pair.first << "  ";
        }
        std::cout << std::endl;

    }

    void displayFirms() const override {
        if (fs.empty()) {
            std::cout << "No firms available." << std::endl;
            return;
        }

        for (const auto& pair : fs) {
            displayFirm(pair.first);
        }
    }
};

#endif