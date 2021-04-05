var data = [
    ["Romania","Cluj"],
    ["Romania","Timisoara"],
    ["Romania","Deva"],
    ["England","London"],
    ["England","Manchester"],
    ["England","Liverpool"],
    ["Germany","Berlin"],
    ["Germany","Hamburg"],
    ["Italy","Rome"],
    ["Italy","Milan"],
    ["Italy","Naples"]
];

function makeBox(myData,filterOption){
    const filteredArray = myData.filter(r => r[0] == filterOption);
    const uniqueOptions = new Set();
    filteredArray.forEach(r => uniqueOptions.add(r[1]));
    
    const uniqueList = [...uniqueOptions];

    const selectCities = document.getElementById("cities");
    selectCities.innerHTML="";
    uniqueList.forEach(item => {
        const option = document.createElement("option");
        option.textContent=item;
        selectCities.appendChild(option);
    });
}

function Apply(){
    const selectCountryValue = document.getElementById("countries").value;
    makeBox(data,selectCountryValue);
}

function afterDocLoads(){
    Apply();
}

document.getElementById("countries").addEventListener("change",Apply);
document.addEventListener("DOMContentLoaded",afterDocLoads);
/*[...]-makes the set an array */