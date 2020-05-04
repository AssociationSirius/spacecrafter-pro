#include"app.hpp"

App::App() {
    core = new Core();
    coreLink = new CoreLink(core);
    ui = new Ui(core, this);
    commander = new AppCommandInterface(core, coreLink, this, ui);
    commander->init();

    pCore1 = new CoreMode1();
    pCore2 = new CoreMode2();
    pCore3 = new CoreMode3();

    pCore = pCore1;

}

App::~App() {
    delete commander;
    delete core;
    delete ui;
}

void App::init() {
    core->init();
    ui->init();
}

void App::update() {
    ui->update();
    core->update();
}

void App::draw() {
    core->draw();
    ui->draw();
}

void App::start_main_loop() {
    int i = 0;

    while(i != 1){

        this->update();
        this->draw();

        i++;
    }
}