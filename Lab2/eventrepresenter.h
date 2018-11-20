/**
  eventrepresenter.h
  Purpose: initializate event with string and chance
 */

#ifndef EVENTREPRESENTER_H
#define EVENTREPRESENTER_H
#include <QString>
#include <QVariant>

class EventRepresenter
{
public:
    EventRepresenter();
    EventRepresenter(int chance, const QString &text);
    ~EventRepresenter();

    /**
     * represents chance of event
     *
     * @brief chance
     * @return chance of event
     */
    int chance() const;

    /**
     * represents text of event
     *
     * @brief text
     * @return text of event
     */
    QString text() const;

private:
    int _chance;
    QString _text;
};

Q_DECLARE_METATYPE(EventRepresenter);
#endif // EVENTREPRESENTER_H
