#include "game_context.hpp"
#include "managers.hpp"
#include "systems.hpp"
#include "entities.hpp"
#include "notifications.hpp"

class AbstractGame {
private:
    SharedGameContext * gameContext;

public:
    AbstractGame() {}

    virtual void onStartUp() =0;
    virtual void onPostStartUp() =0;
    virtual void onBuild() =0;
    virtual void onSetup() =0;
    virtual void onRunOnce() =0;
    virtual void onRun()  =0;
    virtual void onQuit() =0;
    virtual void onExit() =0;
};