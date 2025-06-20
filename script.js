document.getElementById("plannerForm").addEventListener("submit", function(e) {
  e.preventDefault();

  const start = document.getElementById("start").value.trim();
  const destinations = document.getElementById("destinations").value
    .split(",")
    .map(d => d.trim());
  const time = parseInt(document.getElementById("time").value);

  // Simulated itinerary planning (replace with real logic later)
  const route = [start, ...destinations];
  const totalTime = (time * 0.9).toFixed(1); // 90% usage simulation

  let outputHTML = `
    <h3>Suggested Itinerary</h3>
    <ul>
      ${route.map((place, index) => `<li>${index + 1}. ${place}</li>`).join("")}
    </ul>
    <p><strong>Total Estimated Time:</strong> ${totalTime} hours</p>
    <p><strong>Note:</strong> Based on shortest travel time and moderate crowd levels.</p>
  `;

  document.getElementById("output").innerHTML = outputHTML;
});
const map = L.map('map').setView([30.0869, 78.2676], 12); // Default view: Rishikesh

L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
  attribution: 'Map data © <a href="https://openstreetmap.org">OpenStreetMap</a> contributors',
}).addTo(map);

let control = null;

document.getElementById("locationForm").addEventListener("submit", async function (e) {
  e.preventDefault();

  const source = document.getElementById("source").value;
  const destination = document.getElementById("destination").value;

  // Use Nominatim (OpenStreetMap) API to get coordinates
  const getCoords = async (place) => {
    const res = await fetch(`https://nominatim.openstreetmap.org/search?format=json&q=${place}`);
    const data = await res.json();
    if (data.length === 0) throw new Error("Location not found");
    return [parseFloat(data[0].lat), parseFloat(data[0].lon)];
  };

  try {
    const sourceCoords = await getCoords(source);
    const destCoords = await getCoords(destination);

    // Clear previous route
    if (control) map.removeControl(control);

    // Show route
    control = L.Routing.control({
      waypoints: [
        L.latLng(sourceCoords[0], sourceCoords[1]),
        L.latLng(destCoords[0], destCoords[1])
      ],
      routeWhileDragging: false
    }).addTo(map);
  } catch (error) {
    alert("Error: " + error.message);
  }
});
// Script for Contact Form Submission
document.getElementById("contactForm").addEventListener("submit", function(e) {
  e.preventDefault();

  const name = document.getElementById("name").value;
  const email = document.getElementById("email").value;
  const message = document.getElementById("message").value;

  if (name && email && message) {
    document.getElementById("formResponse").innerHTML = "Thank you for contacting us, " + name + "! We will get back to you shortly.";
    document.getElementById("contactForm").reset();  // Clear the form
  } else {
    document.getElementById("formResponse").innerHTML = "Please fill out all fields.";
  }
});
fetch('data/routes.json')
  .then(response => response.json())
  .then(data => {
    console.log("Route data:", data);
    // use data to show on map
  });
