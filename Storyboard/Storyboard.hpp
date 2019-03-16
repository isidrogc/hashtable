//
//  Storyboard.hpp
//  work
//
//  Created by admin on 16/03/2019.
//  Copyright © 2019 admin. All rights reserved.
//

#ifndef Storyboard_hpp
#define Storyboard_hpp

#include <stdio.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include "HashTable.h"

class Note {
    
public:
    Note(const std::string & title,
         const std::string & text,
         const std::vector<std::string> & tags) : m_title(title), m_text(text), m_tags(tags)
    {}
    
    Note (const Note & n): m_title(n.m_title), m_text(n.m_text), m_tags(n.m_tags)
    {}
    
    const std::string & getTitle() const {return m_title;}
    const std::string & getText() const {return m_text;}
    const std::vector<std::string> & getTags() const {return m_tags;}
    
    bool operator()(Note & aNote) const
    {
        return aNote.getTitle() == m_title && aNote.getText() == m_text && aNote.getTags() == m_tags;
    }
    
    bool operator==(const Note & n) const
    {
        return n.getTitle() == m_title && n.getText() == m_text && n.getTags() == m_tags;
    }

private:
    std::string m_title;
    std::string m_text;
    std::vector<std::string> m_tags;
};

class Storyboard {
  
public:
    void addNote(const Note & note) {
        m_titleLookup.addObject(note.getTitle(), note);
        m_textLookup.addObject(note.getText(), note);
        
        for (const auto & tag : note.getTags() ) {
            m_tagsLookup.addObject(tag, note);
        }
    }
    
    void deleteNote (const Note & note) {
        delete(m_titleLookup.deleteObject(note));
        delete(m_textLookup.deleteObject(note));
        delete(m_tagsLookup.deleteObject(note));
    }

    std::vector<const Note *> searchByTitle(const std::string & title){
        return m_titleLookup.searchObjects(title);
    }
    
    std::vector<const Note *> searchByText(const std::string & text) {
        return m_textLookup.searchObjects(text);
    }
    
    std::vector<const Note *> searchByTags(const std::vector<std::string> & tags) {
        
        const auto & tag = tags.begin();
        auto objects = m_tagsLookup.searchObjects(*tag);
        
        auto removeUser = [&tags](auto note)-> bool
        {
            for (const auto & tag : tags)
            {
                auto ltags = note->getTags();
                auto result = std::find(ltags.begin(), ltags.end(), tag );
                if (result == ltags.end()) return true;
            }
            return false;
        };
        
        auto it = std::remove_if(objects.begin(), objects.end(), removeUser);
        objects.erase( it, objects.end() );
        return objects;
    }
    
    
private:
   
    HashTable<std::string, Note> m_titleLookup;
    HashTable<std::string, Note> m_textLookup;
    HashTable<std::string, Note> m_tagsLookup;
    
    
    std::mutex m_lookupAccessLock;
};




#endif /* Storyboard_hpp */
