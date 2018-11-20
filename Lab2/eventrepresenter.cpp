/**
  eventrepresenter.cpp
  Purpose: initializate event with string and chance
 */
#include "eventrepresenter.h"
EventRepresenter::EventRepresenter(int chance, const QString &text) :
    _chance(chance),
    _text(text) {}


EventRepresenter::EventRepresenter() :
    _chance(0),
    _text("") {}

EventRepresenter::~EventRepresenter() {}

//represents chance of event
int EventRepresenter::chance() const
{
    return _chance;
}

//represents text of event
QString EventRepresenter::text() const
{
    return _text;
}
