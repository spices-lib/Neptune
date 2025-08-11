import { signout } from '../actions/Auth'

export default function Page() {

    return (
        <div>
            <p>
                My dashboard
            </p>
            <button onClick={ () => signout() } >
                Sign out
            </button>
        </div>
    )
}