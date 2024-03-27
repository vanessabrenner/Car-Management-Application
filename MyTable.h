#pragma once
#include <QAbstractTableModel>
#include <vector>

#include "car_domain.h"

using std::vector;

class MyTableModel : public QAbstractTableModel {
private:
	vector<Car> cars;
public:
	MyTableModel(const vector<Car> _cars) : cars{ _cars } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return cars.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {

		if (role == Qt::BackgroundRole) {
			QModelIndex i = index.sibling(index.row(), 1);
			if (i.data().toString() == "Mercedes") {
				QBrush bg(Qt::yellow);
				return bg;
			}
		}

		if (role == Qt::DisplayRole) {
			Car c = cars[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(c.getNrInmatriculare());
			}
			if (index.column() == 1) {
				return QString::fromStdString(c.getProducator());
			}
			if (index.column() == 2) {
				return QString::fromStdString(c.getModel());
			}
			if (index.column() == 3) {
				return QString::number(c.getTip());
			}
		}

		return QVariant{};
	}

	//bool setData(const QModelIndex& index, const QVariant& value, int role) override{
	//	
	//	if (role == Qt::EditRole) {
	//		int row = index.row();
	//		int column = index.column();
	//		//save value from editor to member m_gridData
	//		cars[index.row()][index.column()] = value.toString();
	//		//make sure the dataChange signal is emitted so all the views will be notified
	//			QModelIndex topLeft = createIndex(row, column);
	//		emit dataChanged(topLeft, topLeft);
	//	}
	//	return true;
	//}

	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	void setCars(const vector<Car>& cars) {
		this->cars = cars;		
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomR);
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const {

		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return "Numar inmatriculare";
				case 1:
					return "Producator";
				case 2:
					return "Model";
				case 3:
					return "Tip";
				}
			}
		}
		return QVariant{};
	}

};