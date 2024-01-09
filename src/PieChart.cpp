#include "PieChart.h"
#include "stdafx.h"
using namespace std;

///////////////////////
/// implementation ////
///////////////////////

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
