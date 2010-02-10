#ifndef __AWORD_H__
#define __AWORD_H__
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>

#include <boost/serialization/string.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <string>
#include <list>
class aword
{

private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(_word);
    ar & BOOST_SERIALIZATION_NVP(_weight);
    ar & BOOST_SERIALIZATION_NVP(_times);
    ar & BOOST_SERIALIZATION_NVP(_atts);
  }
public:
  std::string _word;
  float _weight;
  short _times;
  std::string _atts;
  aword(std::string word,float weight,short times,std::string atts)
    :_word(word),_weight(weight),_times(times),_atts(atts)
  {
    
  }
};
class words
{
private:
  std::list<aword> _words;
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(_words);
  }
public:
  
  void addWord(aword w)
  {
    _words.push_back(w);
  }
};
#endif
