#include <pigaco/App.hpp>
#include <pigaco/DirectoryScanner.hpp>
#include <QList>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WImage>
#include <QFile>

#include <Wt/WFileUpload>
#include <Wt/WPushButton>
#include <Wt/WProgressBar>
#include <Wt/WDialog>
#include <Wt/WMessageBox>

#include <pigaco/WebGames.hpp>

#include <easylogging++.h>

#include <pigaco/packaging/PackageManager.hpp>
#include <pigaco/packaging/Package.hpp>

namespace pigaco
{

WebGames::WebGames(App *app, Wt::WContainerWidget *parent)
    : Wt::WContainerWidget(parent), m_app(app)
{
    m_dirScanner = app->getDirectoryScanner();

    Wt::WTable *gamesTable = new Wt::WTable(this);
    gamesTable->setHeaderCount(1);

    gamesTable->elementAt(0, 0)->addWidget(new Wt::WText("Logo"));
    gamesTable->elementAt(0, 1)->addWidget(new Wt::WText("Name"));
    gamesTable->elementAt(0, 2)->addWidget(new Wt::WText("Description"));
    gamesTable->elementAt(0, 3)->addWidget(new Wt::WText("Author"));
    gamesTable->elementAt(0, 4)->addWidget(new Wt::WText("Version"));

    for(int i = 0; i < m_dirScanner->getGames().count(); ++i)
    {
        Game *game = m_dirScanner->getGames()[i].get();

        gamesTable->elementAt(i + 1, 0)->addWidget(new Wt::WImage("../../" + game->getConfig(piga::GameHost::Logo)));
        gamesTable->elementAt(i + 1, 1)->addWidget(new Wt::WText(game->getConfig(piga::GameHost::Name)));
        gamesTable->elementAt(i + 1, 2)->addWidget(new Wt::WText(game->getConfig(piga::GameHost::Description)));
        gamesTable->elementAt(i + 1, 3)->addWidget(new Wt::WText(game->getConfig(piga::GameHost::Author)));
        gamesTable->elementAt(i + 1, 4)->addWidget(new Wt::WText(game->getConfig(piga::GameHost::Version)));
    }

    Wt::WText *packagesHeading = new Wt::WText("<h2>Package Management</h2>");
    this->addWidget(packagesHeading);

    Wt::WText *packagesExplanation = new Wt::WText("Packages contain games and applications and can be installed on every pigaco machine. Please "
            "consult the manual for further explanation on the packaging system.");
    this->addWidget(packagesExplanation);

    Wt::WText *installNewPackage = new Wt::WText("<h3>Install Package</h3>");
    this->addWidget(installNewPackage);

    Wt::WFileUpload *newPackageUpload = new Wt::WFileUpload(this);
    newPackageUpload->setFileTextSize(100 * 1000 * 1000 * 1000);
    newPackageUpload->setProgressBar(new Wt::WProgressBar());
    newPackageUpload->setMargin(10, Wt::Right);

    Wt::WPushButton *newPackageUploadButton = new Wt::WPushButton("Upload", this);
    newPackageUploadButton->setMargin(10, Wt::Left | Wt::Right);
    
    newPackageUploadButton->clicked().connect(std::bind([=]() {
        newPackageUpload->upload();
        newPackageUploadButton->disable();
    }));   

    newPackageUpload->changed().connect(std::bind([=]() {
        newPackageUpload->upload();
        newPackageUploadButton->disable();
    }));

    newPackageUpload->uploaded().connect(std::bind([=]() {
        std::string uploadedFile = newPackageUpload->spoolFileName();
        LOG(INFO) << "Uploaded file \"" << newPackageUpload->clientFileName() << "\" to \"" << uploadedFile << "\"";
        newPackageUpload->stealSpooledFile();
        processUploadedFile(uploadedFile);
    }));
    newPackageUpload->fileTooLarge().connect(std::bind([=]() {
    
    }));

    Wt::WText *packagesListHeading = new Wt::WText("<h3>Installed Packages</h3>", this);

    Wt::WTable *packagesTable = new Wt::WTable(this);
    packagesTable->setHeaderCount(1);

    packagesTable->elementAt(0, 0)->addWidget(new Wt::WText("Name"));
    packagesTable->elementAt(0, 1)->addWidget(new Wt::WText("Author"));
    packagesTable->elementAt(0, 2)->addWidget(new Wt::WText("Version"));

    int i = 0;

    for(auto package : m_app->getPackageManager()->getPackages())
    {
        ++i;

        packagesTable->elementAt(i, 0)->addWidget(new Wt::WText(package.second->getConfigVar(packaging::Package::Name)));
        packagesTable->elementAt(i, 1)->addWidget(new Wt::WText(package.second->getConfigVar(packaging::Package::Author)));
        packagesTable->elementAt(i, 2)->addWidget(new Wt::WText(package.second->getVersion().asString()));
    }
}
WebGames::~WebGames()
{

}
void WebGames::processUploadedFile(const std::string &filepath)
{
    packaging::PackagePtr package = m_app->getPackageManager()->getTempPackage(filepath);

    if(!package->isValid()) 
    {
        Wt::WMessageBox *messageBox = new Wt::WMessageBox();
        messageBox->setWindowTitle("Invalid Package");
        messageBox->setText("The uploaded package could not be read!");
        messageBox->setStandardButtons(Wt::Ok);
        messageBox->setIcon(Wt::Information);
        messageBox->show();

        QFile::remove(QString::fromStdString(filepath));

        messageBox->buttonClicked().connect(std::bind([=]() {
            delete messageBox;
        }));

        return;
    }

    Wt::WMessageBox *messageBox = new Wt::WMessageBox();
    
    messageBox->setWindowTitle("Install the uploaded package?");
    messageBox->setText("Do you want to install the package \"" 
            + package->getConfigVar(packaging::Package::Name) + "\" with  the version \"" + package->getVersion().asString() + "\", made by \""
            + package->getConfigVar(packaging::Package::Author) + "\"?");
    messageBox->setStandardButtons(Wt::Yes | Wt::No);
    messageBox->setModal(false);
    messageBox->setIcon(Wt::Information);

    messageBox->buttonClicked().connect(std::bind([=]() {
        if(messageBox->buttonResult() == Wt::Yes)
        {
            m_app->getPackageManager()->installPackage(package.get());

        }
        QFile::remove(QString::fromStdString(filepath));

        delete messageBox;
    }));

    messageBox->show();
}

}
