#include "LineChart.h"
#include "stdafx.h"
using namespace std;

//////////////////////////////////////
///     Static void function     /////
//////////////////////////////////////

// the data part of the HTML for the line chart
static void writeLineChartData(ostream& out, const vector<double>& x, const vector<double>& y) {
    int numPoints = (int)x.size();
    ASSERT((int)x.size() == (int)y.size());

    // start writing to ostream
    out << "data.addColumn('number', 'X')\n";
    out << "data.addColumn('number', 'f(x)')\n";
    out << "data.addRows([\n";
    for (int i = 0; i < numPoints; i++) {

        if (i != numPoints - 1) {
            out << "[" << x[i] << ", " << y[i] << "], ";
        }
        else {
            out << "[" << x[i] << ", " << y[i] << "]\n";
        }
    }
    out << "])\n";
}

// the top part of the HTML for the line chart
static void writeTopBoilerPlateOfLineChart(ostream& out) {
    out << "<html>\n";
    out << "<head>\n";
    out << "<script type = \"text/javascript\" src = \"https://www.gstatic.com/charts/loader.js\"></script>\n";
    out << "<script type = \"text/javascript\">\n";
    out << "google.charts.load('current', {packages: ['corechart', 'line'] });\n";
    out << "google.charts.setOnLoadCallback(drawBackgroundColor);\n";
    out << "function drawBackgroundColor() {\n";
    out << "var data = new google.visualization.DataTable();\n";
}

// the bottom part of the HTML for the line chart
static void writeBottomBoilerPlateOfLineChart(ostream& out) {
    out << "var options = {\n";
    out << "hAxis: {\n";
    out << "title: 'x'\n";
    out << "},\n";
    out << "vAxis : {\n";
    out << "title: 'y'\n";
    out << "},\n";
    out << "backgroundColor : '#f1f8e9'\n";
    out << "};\n";

    out << "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n";
    out << "chart.draw(data, options);\n";
    out << "}\n";
    out << "</script>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<div id = \"chart_div\" style = \"width: 1000px; height: 500px\"></div>\n";
    out << "</body>\n";
}

////////////////////////////
///    Implementation   ////
////////////////////////////

void LineChart::addEntry(double xValue, double yValue) {
    xValues.push_back(xValue);
    yValues.push_back(yValue);
}

void LineChart::setSeries(vector<double> Xs, vector<double> Ys) {
    xValues = Xs;
    yValues = Ys;
}

void LineChart::writeAsHTML(ostream& out) const {
    writeTopBoilerPlateOfLineChart(out);
    writeLineChartData(out, xValues, yValues);
    writeBottomBoilerPlateOfLineChart(out);
}

void LineChart::writeAsHTML(const string& file) const {
    ofstream out;
    out.open(file.c_str());
    writeAsHTML(out);
    out.close();
}

/////////////////////////
///     Testing     /////
/////////////////////////

static void testWriteLineChartData() {

    // generate output from the function
    vector<double> x(3), y(3);
    for (int i = 0; i < 3; i++) {
        x[i] = i;
        y[i] = i * i;
    }
    stringstream out;
    writeLineChartData(out, x, y);
    string outputString = out.str();
    DEBUG_PRINT("outputString\n" << outputString);

    // generate expected output
    stringstream expected;
    expected << "data.addColumn('number', 'X')\n";
    expected << "data.addColumn('number', 'f(x)')\n";
    expected << "data.addRows([\n";
    expected << "[0, 0], [1, 1], [2, 4]\n";
    expected << "])\n";
    string expectedStr = expected.str();
    DEBUG_PRINT("expectedStr\n" << expectedStr);

    ASSERT(outputString == expectedStr);

}

static void testLineChartClass() {
    LineChart lineChart;
    lineChart.addEntry(1.0, 1.0);
    lineChart.addEntry(2.0, 4.0);
    lineChart.addEntry(3.0, 9.0);
    lineChart.addEntry(4.0, 16.0);
    lineChart.addEntry(5.0, 25.0);
    lineChart.writeAsHTML("./outputFiles/xSquare.html");
}

void testLineChart() {
    setDebugEnabled(true);
    TEST(testWriteLineChartData);
    TEST(testLineChartClass);
}