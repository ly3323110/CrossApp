//
//  RootViewController.cpp
//  project
//
//  Created by  on 14-4-11.
//
//

#include "RootViewController.h"



void RootViewController::viewDidLoad()
{
    CCRect rect = this->getView()->getBounds();
    
    CCRect tableRect = rect;
    tableRect.size.height = rect.size.height - 80;

    tableView = new CATableView();
    tableView->initWithFrame(tableRect);
    tableView->setTableViewDataSource(this);
    tableView->setTableViewDelegate(this);
    this->getView()->addSubview(tableView);
    tableView->release();
    
    CAImageView* v = CAImageView::createWithImage(CAImage::create("2.jpg"));
    tableView->setTableHeaderHeight(400);
    tableView->setTableHeaderView(v);
    
    CAView* v2 = CAView::createWithFrame(CCRectZero, ccc4(80, 80, 180, 255));
    tableView->setTableFooterHeight(200);
    tableView->setTableFooterView(v2);
    
    CAView* s = CAView::createWithFrame(CCRectZero, ccc4(127, 255, 127, 127));
    tableView->setTablePullUpView(s);
    tableView->setTablePullViewHeight(200);
    
    tableView->setBackGroundImage(CAImage::create("bg.jpg"));
    
    CAButton* btn2 = CAButton::createWithFrame(CCRect(200, tableRect.size.height+10, 320, 60), CAButtonTypeRoundedRect);
    btn2->setTitleForState(CAControlStateNormal, "un-allowsMultiple");
    btn2->setTitleForState(CAControlStateSelected, "allowsMultiple");
    this->getView()->addSubview(btn2);
    btn2->addTarget(this, CAControl_selector(RootViewController::setAllowsMultipleSelection), CAControlEventTouchUpInSide);
    //btn2->setAllowsSelected(true);
    //btn2->setControlStateLocked(true);
    
    CASwitch* s3 = CASwitch::createWithFrame(CCRect(10, tableRect.size.height+10, 120, 60));
    s3->addTarget(this, CAControl_selector(RootViewController::setAllowsSelection), CAControlEventTouchUpInSide);
    this->getView()->addSubview(s3);
    
    //CAScheduler::schedule(schedule_selector(RootViewController::updateProgress), this, 5, false);
    
}

void RootViewController::viewDidUnload()
{

}

bool RootViewController::setAllowsSelection(CAControl* sender, CCPoint point)
{
    CASwitch* switch_ = (CASwitch*)sender;
    
    if (switch_->isOn() == false)
    {
        tableView->setAllowsSelection(false);
    }
    else
    {
        tableView->setAllowsSelection(true);
    }
    
    tableView->reloadData();
    
    
    return true;
}

bool RootViewController::setAllowsMultipleSelection(CAControl* sender, CCPoint point)
{
	CAButton* btn = (CAButton*)sender;
//    
//	if (btn->isSelected())
//    {
//        tableView->setAllowsMultipleSelection(false);
//    }
//    else
//    {
//        tableView->setAllowsMultipleSelection(true);
//    }
//    
//    tableView->reloadData();
    
    CCRect rect = btn->getFrame();
    rect.size.width += 10;
    
    btn->setFrame(rect);
    
    return true;
}

void RootViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    char s[32];
    sprintf(s, "viewControll = %ld",this->getNavigationController()->getViewControllerCount());
    
    RootViewController* viewController = new RootViewController();
    viewController->init();
    viewController->setNavigationBarItem(CANavigationBarItem::create(s));
    viewController->setTitle("view1");
    
    this->getNavigationController()->pushViewController(viewController, true);
    viewController->autorelease();
    
    CCLog("selected = %d %d",section, row);
}

void RootViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    CCLog("deselected = %d %d",section, row);
}

CATableViewCell* RootViewController::tableCellAtIndex(CATableView *table, unsigned int section, unsigned int row)
{
    
    
    CATableViewCell* cell = table->dequeueReusableCellWithIdentifier("aaa");
    if (cell == NULL)
    {
        cell = CATableViewCell::create("aaa");
        //cell->setBackGroundView(NULL);
    }
    
    CCString* str = CCString::createWithFormat("CELL - %u", row);
    CCLabelTTF* ttf = CCLabelTTF::create(str->getCString(), "Arial", 40);
    ttf->setColor(ccBLACK);
    ttf->setFrame(CCRect(10, 60, 0, 0));
    cell->addSubview(ttf);
    
//    CALabel* label = CALabel::create(CCRect(0, 0, 600, 100));
//    label->setOpacity(128);
//    label->setVerticalTextAlignmet(kCCVerticalTextAlignmentCenter);
//    label->setCenterOrigin(CCPoint(300, 60));
//    label->setText(str->getCString());
//    cell->addSubview(label);
    
    return cell;
    
}

CAView* RootViewController::tableViewSectionViewForHeaderInSection(CATableView* table, unsigned int section)
{
    CAView* view = CAView::createWithFrame(CCRect(0, 0, 0, 0), ccc4(200, 200, 255, 255));
    
    CCString* str = CCString::createWithFormat("Header - %u", section);
    CCLabelTTF* ttf = CCLabelTTF::create(str->getCString(), "Arial", 20);
    ttf->setColor(ccc3(127, 127, 127));
    ttf->setFrame(CCRect(10, 10, 0, 0));
    view->addSubview(ttf);
    
    return view;
}

CAView* RootViewController::tableViewSectionViewForFooterInSection(CATableView* table, unsigned int section)
{
    CAView* view = CAView::createWithFrame(CCRect(0, 0, 0, 0), ccc4(200, 255, 200, 255));
    
    CCString* str = CCString::createWithFormat("Footer - %u", section);
    CCLabelTTF* ttf = CCLabelTTF::create(str->getCString(), "Arial", 20);
    ttf->setColor(ccc3(127, 127, 127));
    ttf->setFrame(CCRect(10, 10, 0, 0));
    view->addSubview(ttf);
    
    return view;
}
unsigned int RootViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    return 30;
}

unsigned int RootViewController::numberOfSections(CATableView *table)
{
    return 3;
}

unsigned int RootViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return 120;
}

unsigned int RootViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return 40;
}

unsigned int RootViewController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
    return 40;
}

void RootViewController::tableViewDidShowPullDownView(CATableView* table)
{
    CCLog("----------down");
}

void RootViewController::tableViewDidShowPullUpView(CATableView* table)
{
    CCLog("----------up");
}

