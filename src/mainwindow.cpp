#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <memory>
#include "sudoku.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	int row = 0;
	int col = 1;

	for (int i = 0; i < 81; i++) {
		QLineEdit *edit = new QLineEdit(this);
		edit->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9]"), edit));
		edit->setMaxLength(1);

		if (i % 9 == 0) {
			row++;
			col = 1;
		}

		if (row % 4 == 0 || col % 4 == 0) {
			QSpacerItem *item = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
			ui->gridLayout->addItem(item, row, col);
			row = row % 4 == 0 ? row + 1 : row;
			col = col % 4 == 0 ? col + 1 : col;
		}

		ui->gridLayout->addWidget(edit, row, col++);
		boxes.append(edit);
	}

	connect(ui->solveButton, &QPushButton::released, this, &MainWindow::handleSolveButton);
	connect(ui->clearButton, &QPushButton::released, this, &MainWindow::handleClearButton);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::handleSolveButton()
{
	std::array<int, 81> grid;

	for (int i = 0; i < 81; i++) {
		grid[i] = boxes[i]->text().toInt();
	}

	auto sudoku = std::make_unique<Sudoku>(grid);

	if (!sudoku->validInput()) {
		QMessageBox::warning(this, " ", "Invalid input", QMessageBox::Ok);
		return;
	}

	if (sudoku->solveSudoku()) {
		for (int i = 0; i < 81; i++) {
			boxes[i]->setText(QString::number(grid[i]));
		}
	} else {
		QMessageBox::warning(this, " ", "No solution found", QMessageBox::Ok);
	}
}

void MainWindow::handleClearButton()
{
	for (const auto &i : boxes) {
		i->setText("");
	}
}
