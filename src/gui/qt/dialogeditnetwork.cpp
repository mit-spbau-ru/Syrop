#include "dialogeditnetwork.h"
#include "ui_dialogeditnetwork.h"
#include "qmessagebox.h"
#include "datamodel.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <vector>

using namespace std;

DialogEditNetwork::DialogEditNetwork(QWidget *parent, const QString &networkName)
    : QDialog(parent)
    , ui(new Ui::DialogEditNetwork)
    , networkName(networkName)
    , isEdited(false)
{
    ui->setupUi(this);
    
    ui->verticalLayout->setMargin(10);
    this->setLayout(ui->verticalLayout);
    ui->pushButtonSave->setEnabled(false);
    ui->labelErrorMessage->clear();
    
    attrs = DataModel::getInstance()->loadNetworkSettings(networkName);
    
    std::string sum = "";
    for(utils::attributes::iterator it = attrs.begin(); 
        it != attrs.end(); it++) {
        sum.append(it->first + "=" + it->second + "\n");
    }
            
    ui->plainTextEditNetworkSettings->setPlainText(QString(sum.c_str()));
    connect(ui->plainTextEditNetworkSettings, SIGNAL(textChanged()),
            this, SLOT(onChanged()));  
    connect(ui->pushButtonSave, SIGNAL(clicked()),
            this, SLOT(onSave()));
    connect(ui->pushButtonCheck, SIGNAL(clicked()),
            this, SLOT(checkText()));
 
}

void DialogEditNetwork::onChanged()
{
    ui->pushButtonSave->setEnabled(true);
    ui->labelErrorMessage->clear();
    isEdited = true;
}

void DialogEditNetwork::onSave()
{
    if(!checkText())
        return;
    DataModel::getInstance()->saveNetworkSettings(networkName, attrs);
    isEdited = false;
    ui->pushButtonSave->setEnabled(false);
    this->close();
}

bool DialogEditNetwork::checkText()
{
    static boost::xpressive::sregex const attributes = 
            boost::xpressive::sregex::compile("^\\s*(\\S+){1}\\s*=\\s*(\\S+){1}\\s*$");
    
    string text = ui->plainTextEditNetworkSettings->document()->
            toPlainText().toStdString();
    vector<string> splitVec;
	boost::split(splitVec, text, boost::algorithm::is_any_of("\n"));
	vector<string> errLines;
    int lineNum = 0;
	for (vector<string>::iterator it = splitVec.begin(); it != splitVec.end(); ++it)
	{
        lineNum++;
		boost::trim(*it);
		if ( !it->empty() )
		{
			boost::xpressive::smatch match;
			if (regex_match(*it, match, attributes))
				attrs[match[1].str()] = match[2].str();
			else
                errLines.push_back(
                            boost::lexical_cast<std::string>(lineNum) + ": " + *it);
		}
	}
    
    if(!errLines.empty()) {
         string s = ("Error in line " + *errLines.begin());
         ui->labelErrorMessage->setText(QString(s.c_str()));
    }
    else
        ui->labelErrorMessage->clear();
    
    return errLines.empty();
    
}

DialogEditNetwork::~DialogEditNetwork()
{
    delete ui;
}
