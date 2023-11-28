async function handleChange(event) {
  await fetch("/api/led", { method: event.target.checked ? "DELETE" : "POST" });
}

async function handleLoaded() {
  const res = await fetch("/api/led").then((res) => res.json());
  document.getElementById("toggle").checked = res.led === "off";
}

function handleConnect() {
  const ws = new WebSocket(`ws://${window.location.hostname}/ws`);

  ws.onclose = () => setTimeout(handleConnect, 1000);
  ws.onmessage = (event) => (document.getElementById("toggle").checked = JSON.parse(event.data).led === "off");
}

handleLoaded();
handleConnect();
