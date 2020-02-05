const socket = io()

//Elements
const $messageForm = document.querySelector('#message-form')
const $messageFormInput = $messageForm.querySelector('input')
const $messageFormButton = $messageForm.querySelector('button')
const $sendLocationButton = document.querySelector('#send-location')
const $messages = document.querySelector('#messages')

//template
const messageTemplate = document.querySelector('#message-template').innerHTML
const locationTemplate = document.querySelector('#location-template').innerHTML
const sidebarTemplate = document.querySelector('#sidebar-template').innerHTML

//options
const {username, room} = Qs.parse(location.search, {ignoreQueryPrefix:true})


const autoScroll = () => {
	//New message element
	const $newMessage = $messages.lastElementChild //the last element

	//Get the height of the new message
	const newMessageStyles = getComputedStyle($newMessage) //available by the browser
	const newMessageMargin = parseInt(newMessageStyles.marginBottom) 
	const newMessageHeigth = $newMessage.offsetHeight + newMessageMargin // the height of the message

	//Visible height
	const visibleHeight = $messages.offsetHeight

	//Height of messages container
	const containerHeight = $messages.scrollHeight //the height we are able to scroll through

	const scrollOffset = $messages.scrollTop + visibleHeight// how far we actually scrolled

	if(containerHeight - newMessageHeigth <= scrollOffset){ //if we scrolled to the bottom before the new message
		$messages.scrollTop = $messages.scrollHeight //scroll to the bottom
	}
}

socket.on("message", (message) => {
	const html = Mustache.render(messageTemplate, {
		createdAt: moment(message.createdAt).format('H:mm'),
		message: message.text,
		username: message.username
	})
	$messages.insertAdjacentHTML('beforeend', html)
	autoScroll()
})

socket.on("locationMessage", (url) => {
	const html = Mustache.render(locationTemplate, {
		createdAt: moment(url.createdAt).format('H:mm'),
		url: url.url,
		username: url.username
	})
	$messages.insertAdjacentHTML('beforeend', html)
	autoScroll()
})

socket.on("roomData", ({room, users}) => {
	const html = Mustache.render(sidebarTemplate, {
		room,
		users
	})
	document.querySelector('#sidebar').innerHTML = html
})

$messageForm.addEventListener('submit', (e) => {
	e.preventDefault()

	//disable
	$messageFormButton.setAttribute('disabled', 'disabled')
	
	const message = e.target.elements.message.value
	socket.emit('sendMessage', message, (error) => {

		//enable
		$messageFormButton.removeAttribute('disabled')

		$messageFormInput.value = ''
		$messageFormInput.focus()

		if(error){
			return console.log(error)
		}
		console.log('Message delivered!')
	})
})

$sendLocationButton.addEventListener('click', () => {
    if (!navigator.geolocation) {
        return alert('Geolocation is not supported by your browser.')
    }

    $sendLocationButton.setAttribute('disabled', 'disabled')

    navigator.geolocation.getCurrentPosition((position) => {
        socket.emit('sendLocation', {
            latitude: position.coords.latitude,
            longitude: position.coords.longitude
        }, () => {
            $sendLocationButton.removeAttribute('disabled')
            console.log('Location shared!')  
        })
    })
})

// sending with a callback for acknowledgment

socket.emit('join', {username, room}, (error) => {
	if(error){
		alert(error)
		location.href = '/' //redirect them to the same window
	}
})
