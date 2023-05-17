//
// Created by chiru on 17.05.2023.
//

#ifndef PROIECT1_EVENT_H
#define PROIECT1_EVENT_H

#include "EventTarget.h"
#include "Utilizator.h"

class EventInterface{
public:
    virtual void primeInit() = 0;
    virtual void primeExec(EventTarget* t) = 0;
    virtual ~EventInterface() = default;
};

class EventProperty: public EventInterface, public Istoric{
protected:
    function<void(EventTarget*)> exec;
    EventType tip;
    int prioritate;

public:
    EventProperty(EventType tip, int eventPrioritate,
                  function<void(EventTarget*)> exec) : exec(std::move(exec)),
                                                       Istoric("Event "+eventToStr(tip)){
        this->tip = tip;
        this->prioritate = eventPrioritate;
    }

    void primeInit() override{
        addIstoric("Event initiat");
        init();
    }

    void primeExec(EventTarget* t) override{
        addIstoric("Eveniment executat");
        executa(t);
        exec(t);
    }

    virtual void init() = 0;
    virtual void executa(EventTarget* t) = 0;

    int getPrioritate() const{
        return prioritate;
    }

    EventType getTip(){
        return tip;
    }


    ~EventProperty() override{
        addIstoric("Event distrus");
    }
};

template <typename T>
class Event: public EventProperty{
    T executer;

public:
    Event(EventType tip, int prioritate,
          function<void(EventTarget*)> exec): EventProperty(tip, prioritate, exec){
    }

    void init() override{}

    void executa(EventTarget* t) override{}
};


template<>
class Event<Utilizator*>: public EventProperty{
    Utilizator* executer;

public:
    Event<Utilizator*>(Utilizator* executer, EventType tip, int prioritate,
                       function<void(EventTarget* t)> exec): executer(executer), EventProperty(tip, prioritate, std::move(exec)){

    }

    void init() override{
        if(Staff::eStaff(executer))
            addIstoric("Initializator: staff "+executer->getNume());
        else
            addIstoric("Initializator: user "+executer->getNume());
    }

    void executa(EventTarget* t) override{
        addIstoric("Informatii : "+t->getInfo()+" primite de "+executer->getNume());
        printIstoric(cout);
    }
};

class EventHandler{
    static EventHandler* instance;
    list<EventProperty*> eventuri;

public:
    EventHandler(){
    };
    static EventHandler* getInstance();

    template<typename T>
    void addEvent(Event<T>* event) {
        event->primeInit();
        getInstance()->eventuri.push_back(event);
    }

    static bool sorteazaPrioritate(const EventProperty* obj1, const EventProperty* obj2) {
        return obj1->getPrioritate() < obj2->getPrioritate();
    }

    void propaga(EventType tip, EventTarget* target){
        eventuri.sort(sorteazaPrioritate);
        for(auto* event : eventuri){
            if(event->getTip() == tip){
                event->primeExec(target);
            }
        }
    }

    void cleanup();

    ~EventHandler(){
        cleanup();
    }
};
EventHandler* EventHandler::instance;
EventHandler *EventHandler::getInstance() {
    if(instance == nullptr)
        instance = new EventHandler();


    return instance;
}
void EventHandler::cleanup() {
    for (auto event : eventuri) {
        delete event;
    }
}
#endif //PROIECT1_EVENT_H
