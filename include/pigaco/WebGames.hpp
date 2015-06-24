#pragma once

#include <memory>
#include <Wt/WContainerWidget>

namespace pigaco
{
class App;
class DirectoryScanner;

class WebGames : public Wt::WContainerWidget
{
    public:
        WebGames(App *app, Wt::WContainerWidget *parent = 0);
        virtual ~WebGames();

        void processUploadedFile(const std::string &filepath);
    private:
        App *m_app;
        std::shared_ptr<DirectoryScanner> m_dirScanner;
};
}
