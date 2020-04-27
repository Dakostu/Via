#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "colorgenerator.h"
#include "./ui_mainwindow.h"

#include "../controller/mainwindowcontroller.h"

#include "../model/data.h"

#include "../l10n/localizeduistrings.h"

#include <vector>
#include <memory>
#include <QButtonGroup>
#include <QColorDialog>
#include <QGraphicsScene>
#include <QListView>
#include <QMainWindow>
#include <QToolButton>
#include <type_traits>


QT_BEGIN_NAMESPACE
using namespace Via::UI;
using namespace Via::L10n;
using namespace Via::Model;
using namespace Via::Shapes;
using namespace Via::Control;
using namespace Via::Structures;
using namespace Via::Interfaces;
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

namespace Via::UI {

class MainWindow : public QMainWindow
{

    struct NodeAction : std::integral_constant<bool, true> {};
    struct RouteAction : std::integral_constant<bool, false> {};

    struct RouteIndex : std::integral_constant<bool, true> {};
    struct RouteNodeIndex : std::integral_constant<bool, false> {};

    Q_OBJECT

    Via::Control::MainWindowController &controller;
    Ui::MainWindow *ui;

    ColorGenerator colorGenerator;
    std::unique_ptr<QGraphicsScene> currentScene;
    std::unique_ptr<QButtonGroup> quickButtonGroup;

    std::vector<std::unique_ptr<QAction>> actions;

    size_t selectedRouteIndex;
    size_t selectedRouteNodeIndex;

    void initializeQuickButtons();
    void initializeShapeSelections();
    void initializeRouteBoxUI();
    void initializeRouteSettingsUI();
    void initializeNodeBoxUI();
    void initializeNodeSettingsUI();

    template <typename SelectedIndex>
    void refreshIndex() {
        Via::UI::RouteDataView *dataView;
        size_t *index;

        if constexpr (SelectedIndex::value == RouteIndex::value) {
            getCurrentRoute()->removeTemporaryPreviewNode();
            dataView = ui->routeBoxRouteList;
            index = &selectedRouteIndex;            
        } else {
            dataView = ui->nodeBoxNodeList;
            index = &selectedRouteNodeIndex;
        }

        if (dataView->selectionModel() && dataView->selectionModel()->hasSelection()) {
            *index = static_cast<size_t>(dataView->getSelectedRows()[0].row());
        }

    }

    Via::Shapes::Route* getCurrentRoute();

public:
    MainWindow(QWidget *parent, Via::Control::MainWindowController &newController);
    ~MainWindow();

    QAbstractButton* getQuickButtonMove();
    QAbstractButton* getQuickButtonAutoAdd();
    QAbstractButton* getQuickButtonSelect();

    template <typename OnlyNode>
    void styleChangeEvent(const QString &newStyle) {
        auto currentRoute = getCurrentRoute();

        if constexpr (OnlyNode::value == true) {
            currentRoute->setStyleOfNode(selectedRouteNodeIndex, newStyle);

            auto &currentNode = (*currentRoute)[selectedRouteNodeIndex];
            auto newShapeKey = currentNode.getShapeKey();
            auto isDifferentNow = currentNode.getStyleDiffersFromRoute();
        } else {
            currentRoute->setShapeKey(newStyle);
        }
    }


    template <typename OnlyNode>
    void colorChangeEvent(const QColor &oldColor) {
        auto newColor = QColorDialog::getColor(oldColor, this);
        if (!newColor.isValid()) {
            return;
        }
        auto currentRoute = getCurrentRoute();

        if constexpr (OnlyNode::value == true) {
            currentRoute->setColorsOfNode(selectedRouteNodeIndex, newColor);
            ui->nodeColorButton->changeColor(newColor);
            controller.updateRouteNodeColor(selectedRouteNodeIndex, newColor);
        } else {
            currentRoute->setColors(newColor);
            ui->routeColorButton->changeColor(newColor);
            controller.updateRouteColor(selectedRouteIndex, newColor);
            for (size_t i = 0; i < getCurrentRoute()->getNodeAmount(); ++i) {
                if (!(*getCurrentRoute())[i].getStyleDiffersFromRoute()) {
                    controller.updateRouteNodeColor(i, newColor);
                }
            }
        }

        if (!ui->nodeColorButton->isFlat()) {
            auto &currentSelectedNode = (*controller.getCurrentProject())[selectedRouteIndex][selectedRouteNodeIndex];
            ui->nodeColorButton->changeColor(currentSelectedNode.getColors());
        }
    }

    template <typename OnlyNode>
    void nameChangeEvent(Nameable *data, const QString &newName, const std::function<void(void)> &listUpdateFunc) {
        data->setName(newName);

        listUpdateFunc();

        if constexpr (OnlyNode::value == true) {
            auto nodeHasDefaultName = (data->getName() == (Via::L10n::LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(selectedRouteNodeIndex + 1)));
            data->setNameChangedByUser(!nodeHasDefaultName);

            if (ui->nodeBoxNodeList->selectionModel()->hasSelection()) {
                ui->nodeBoxNodeList->moveSelectionTo(selectedRouteNodeIndex);
            }
        } else {
            auto routeHasDefaultName = (data->getName() == (Via::L10n::LocalizedUIStrings::getUIString("ROUTE_DEFAULT_NAME").arg(selectedRouteIndex + 1)));
            data->setNameChangedByUser(!routeHasDefaultName);
        }

        if (ui->routeBoxRouteList->selectionModel()->hasSelection()) {
            ui->routeBoxRouteList->moveSelectionTo(selectedRouteIndex);
        }
    }


public slots:
    void addRoute();    
    void deleteSelectedRoute();
    void createNewProject();
    void loadProject();
    void saveProject();
    void saveProjectAs();
    void setNoProjectsOpenMode(bool noProjectsOpen);
    void updateRouteList();
    void updateNodeList();
    void routeSelectionEvent();
    void routeNodeSelectionEvent();    
    void routeShowOrderChangeEvent(bool value);
    void moveRouteEvent(int by);
    void getDataFromCurrentProject();
    void disableSettingsBox();
    void activateAutoAddMode();
    void addRouteNode(qreal x, qreal y);
    void deleteSelectedRouteNode();
    void setNodeSettingsEnabled(bool enabled);
    void moveNodeEvent(int by);
    void changeNodeExtraLabel(const QString &text);

signals:
    void routeListChanged();
    void routeNodeListChanged();

};

}
#endif // MAINWINDOW_H
