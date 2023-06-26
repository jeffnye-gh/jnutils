// Define the callback function
function handleChartData(data) {
  // Extract the necessary data from the JSONP response
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

// Dynamically load the JSONP script
function loadJSONP() {
  const script = document.createElement('script');
  script.src = 'data.jsonp';
  document.body.appendChild(script);
}

// Invoke the function to load JSONP data
loadJSONP();

