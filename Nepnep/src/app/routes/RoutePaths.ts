export const ROUTE_PATHS = {
    ROOT: '/',
    SIGN_IN: '/signin',
    SIGN_UP: '/signup'
} as const

export type RoutePath = typeof ROUTE_PATHS[keyof typeof ROUTE_PATHS]