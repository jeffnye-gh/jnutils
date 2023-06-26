// Define the callback function
function handleChartData(data) {
  // Extract the necessary data from the JSON
  const chartType = data['chart-type'];
  const title = data['title'];
  const xLabel = data['x_label'];
  const yLabel = data['y_label'];
  const xTicks = data['x_ticks'];
  const datasets = data['data'];

  // Prepare the data for Chart.js
  const chartData = datasets.map(dataset => ({
    label: dataset.label,
    borderColor: dataset.line_properties.color,
    borderCapStyle: dataset.line_properties.dash_capstyle,
    borderDash: dataset.line_properties.style === 'dashdot' ? [10, 5] : [],
    data: dataset.x.map((x, i) => ({ x, y: dataset.y[i] }))
  }));

  // Create the chart
  const ctx = document.getElementById('myChart').getContext('2d');
  new Chart(ctx, {
    type: chartType,
    data: {
      labels: xTicks,
      datasets: chartData
    },
    options: {
      responsive: true,
      title: {
        display: true,
        text: title
      },
      scales: {
        x: {
          display: true,
          scaleLabel: {
            display: true,
            labelString: xLabel
          }
        },
        y: {
          display: true,
          scaleLabel: {
            display: true,
            labelString: yLabel
          }
        }
      }
    }
  });
}

// Make a request to fetch JSON data from the server
function fetchData() {
  const url = 'http://localhost:3000/data'; // Replace with your server URL
  fetch(url)
    .then(response => response.json())
    .then(data => handleChartData(data))
    .catch(error => console.error('Error fetching data:', error));
}

// Invoke the function to fetch data
fetchData();

