#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Data structure to hold a single data point
struct DataPoint {
    float value;
    Color color;
};

// Data structure to hold a dataset
struct Dataset {
    vector<DataPoint> data;
    string label;
};

// Function to generate a random dataset
Dataset generateRandomDataset(int numPoints, string label) {
    Dataset dataset;
    dataset.label = label;
    for (int i = 0; i < numPoints; i++) {
        DataPoint point;
        point.value = static_cast<float>(rand()) / RAND_MAX * 100.0f;
        point.color = Color::Color(rand() % 255, rand() % 255, rand() % 255);
        dataset.data.push_back(point);
    }
    return dataset;
}

// Function to visualize a dataset
void visualizeDataset(RenderWindow& window, Dataset dataset) {
    Font font;
    font.loadFromFile("arial.ttf");

    Text label(dataset.label, font, 20);
    label.setPosition(10, 10);
    window.draw(label);

    float maxValue = *max_element(dataset.data.begin(), dataset.data.end(), [](const DataPoint& a, const DataPoint& b) { return a.value < b.value; });
    float minValue = *min_element(dataset.data.begin(), dataset.data.end(), [](const DataPoint& a, const DataPoint& b) { return a.value < b.value; });

    float graphWidth = 400;
    float graphHeight = 200;
    float barWidth = graphWidth / dataset.data.size();
    float barSpacing = 2;

    for (int i = 0; i < dataset.data.size(); i++) {
        float barHeight = (dataset.data[i].value - minValue) / (maxValue - minValue) * graphHeight;
        RectangleShape bar(Vector2f(barWidth, barHeight));
        bar.setPosition(10 + i * (barWidth + barSpacing), 250 - barHeight);
        bar.setFillColor(dataset.data[i].color);
        window.draw(bar);
    }
}

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(500, 300), "Responsive Data Visualization Monitor");

    Dataset dataset1 = generateRandomDataset(10, "Dataset 1");
    Dataset dataset2 = generateRandomDataset(10, "Dataset 2");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

        visualizeDataset(window, dataset1);
        visualizeDataset(window, dataset2);

        window.display();
    }

    return 0;
}