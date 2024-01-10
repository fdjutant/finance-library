#include "PieChart.h"
#include "stdafx.h"
using namespace std;

//////////////////////////////////////
///     Static void function     /////
//////////////////////////////////////

// the data part  of the HTML for the pie chart
static void writePieChartData(ostream& out, const vector<string>& labels, const vector<double>& values) {
    int nLabels = (int)labels.size();
    for (int i = 0; i < nLabels; i++) {
        string label = labels[i];
        double value = values[i];
        out << "['" << label << "', " << value << "]";
        if (i == nLabels - 1) {
            out << "\n";
        }
        else {
            out << ",\n";
        }
    }
}

// the top part of the HTML for the pie chart
static void writeTopBoilerPlateOfPieChart(ostream& out) {
    out << "<html>\n";
    out << "<head>\n";
    out << "<script type = \"text/javascript\" src = \"https://www.gstatic.com/charts/loader.js\"></script>\n";
    out << "<script type = \"text/javascript\">\n";
    out << "google.charts.load(\"current\", { packages: [\"corechart\"] });\n";
    out << "google.charts.setOnLoadCallback(drawChart);\n";
    out << "function drawChart() {\n";
    out << "var data = google.visualization.arrayToDataTable([\n";
    out << "['Task', 'Hours per Day'],\n";
}

// the bottom part of the HTML for the pie Chart
static void writeBottomBoilerPlateOfPieChart(ostream& out) {
    out << "]);\n";
    out << "var options = {\n";
    out << "title: 'My Daily Activities',\n";
    out << "is3D : true,\n";
    out << "};\n";
    out << "var chart = new google.visualization.PieChart(document.getElementById('piechart_3d'));\n";
    out << "chart.draw(data, options);\n";
    out << "}\n";
    out << "</script>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<div id = \"piechart_3d\" style = \"width: 900px; height: 500px;\"></div>\n";
    out << "</body>\n";
    out << "</html>\n";
}

////////////////////////////
///    Implementation   ////
////////////////////////////

void PieChart::setTitle(const string& t) {
	title = t;
}

void PieChart::addEntry(const string& label, double value) {
	labels.push_back(label);
	values.push_back(value);
} 

void PieChart::writeAsHTML(ostream& out) const {
    writeTopBoilerPlateOfPieChart(out);
    writePieChartData(out, labels, values);
    writeBottomBoilerPlateOfPieChart(out);
}

void PieChart::writeAsHTML(const string& file) const {
    ofstream out;
    out.open(file.c_str());
    writeAsHTML(out);
    out.close();
}

/////////////////////////
///     Testing     /////
/////////////////////////
static void testWritePieChartData() {

    // generate output from the function
    vector<string> labels(3);
    vector<double> values(3);
    for (int i = 0; i < 3; i++) {
        stringstream ss;
        ss << "A Label " << i;
        labels[i] = ss.str();
        INFO(labels[i]);
        values[i] = (double)i;
    }
    stringstream out;
    writePieChartData(out, labels, values);
    string outString = out.str();

    // compare expected and output
    stringstream expected;
    expected << "['A Label 0', 0],\n";
    expected << "['A Label 1', 1],\n";
    expected << "['A Label 2', 2]\n";
    string expectedStr = expected.str();
    ASSERT(outString == expectedStr);
}

static void testPieChartClass() {
    PieChart pieChart;
    pieChart.addEntry("C++", 50);
    pieChart.addEntry("Python", 40);
    pieChart.addEntry("Java", 10);
    pieChart.writeAsHTML("./outputFiles/codingLang.html");
}

void testPieChart() {
    setDebugEnabled(false);
    TEST(testWritePieChartData);
    TEST(testPieChartClass);
}